## perturb_password() main public function
```py
def perturb_password(password: str, eps: float) -> str:
    unleeted_password = unleet_password(password)
    tokens, token_types = tokenize_password(unleeted_password)

    # Divy up Privacy Budget
    semantic_budget = eps / (len(tokens) + 1)
    diction_budget = (len(tokens) * eps) / (len(tokens) + 1)
    budget_per_token = diction_budget / len(tokens)

    # Diction Perturbment
    for i in range(len(tokens)):
        token = tokens[i]
        token_type = token_types[i]
        if token_type == "word":
            tokens[i] = perturb_word(token, budget_per_token)
        if token_type == "number":
            tokens[i] = perturb_number(token, budget_per_token)
        if token_type == "special":
            tokens[i] = perturb_special(token, budget_per_token)

    # Semantic Perturbment
    perturb_semantics(password, semantic_budget)

    perturbed_password = fix_leet_password(password, ''.join(tokens))

    return perturbed_password
```

## tokenize_password
```py
def tokenize_password(password: str) -> int:
    # Convert password to lowercase and generate all unleeted variants
    lower_password = password.lower()
    unleeted_variants = generate_unleet(lower_password)

    token_count = 0
    i = 0

    while i < len(password) and token_count < 20:
        best_len = 0
        best_total_cost = INF
        best_unleeted_source = None

        # Find best matching dictionary word starting at i across all unleeted variants
        for variant in unleeted_variants:
            costs = find_word_costs(variant[i:])
            for len_candidate in valid_word_lengths(costs):
                if len_candidate <= 2 and not password[i].isalpha():
                    continue

                word_cost = costs[len_candidate - 1]
                follow_cost = best_followup_word_cost(unleeted_variants, i + len_candidate)
                total_cost = word_cost + follow_cost + SPLIT_PENALTY

                if total_cost < best_total_cost:
                    best_total_cost = total_cost
                    best_len = len_candidate
                    best_unleeted_source = variant[i:]

        start_of_token_indices[token_count] = i

        if best_len > 0 and is_valid_word_token(password, i, best_len):
            token_types[token_count] = 'w'
            copy_unleeted_segment(unleeted_pw, i, best_unleeted_source, best_len)
            i += best_len
        elif password[i].isdigit():
            token_types[token_count] = 'n'
            while i < len(password) and password[i].isdigit() and digits_collected < 6:
                unleeted_pw[i] = password[i]
                i += 1
        elif password[i].ispunct():
            token_types[token_count] = 's'
            unleeted_pw[i] = password[i]
            i += 1
        else:
            token_types[token_count] = 'o'
            unleeted_pw[i] = password[i]
            i += 1

        token_count += 1

    cleanup_unleeted_variants(unleeted_variants)
    return token_count
```
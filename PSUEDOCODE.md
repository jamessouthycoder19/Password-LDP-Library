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
```
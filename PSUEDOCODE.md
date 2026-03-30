# Python implementation of potential algorithm
Consideration - split privacy budget among perturbation types

## perturb() main public function
```py
def perturb(password: str, eps: float) -> str:
    # current implementation of tokenize_password (pythonized)
    # tokens = List[str]
    # token_types = List[str]
    tokens, token_types = tokenize_password(password)

    swapping_budget = eps / 2.0
    diction_budget = eps / 2.0

    # swapping occurs in place
    tokens, token_types = perturb_semantics(password, swapping_budget)

    # diction editing will occur in place
    budget_per_token = diction_budget / len(tokens)
    for i in range(len(tokens)):
        token = tokens[i]
        token_type = token_types[i]
        if token_type == "w":
            tokens[i] = perturb_word(token, budget_per_token)
        if token_type == "n":
            tokens[i] = perturb_number(token, budget_per_token)
        if token_type == "s":
            tokens[i] = perturb_special(token, budget_per_token)

    return ''.join(tokens)
```

## perturb_semantics
```py
```
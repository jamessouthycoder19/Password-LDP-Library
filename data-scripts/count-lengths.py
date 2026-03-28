files = [
    "passwords.txt",
    "english_wikipedia.txt",
    "us_tv_and_film.txt",
    "surnames.txt",
    "male_names.txt",
    "female_names.txt",
    ]

for file in files:
    split = False
    if file == "english_wikipedia.txt" or file == "passwords.txt" or file == "us_tv_and_film.txt":
        split = True
    with open("../data/original-wordlists/" + file) as f:
        lines = f.read().splitlines()
    lengths = {}
    for line in lines:
        if split:
            line = line.split()[0]
        length = len(line)
        if length not in lengths:
            lengths[length] = 0
        lengths[length] += 1
    print(f"{file}")
    for length in sorted(lengths.keys()):
        print(f"{length}: {lengths[length]}")
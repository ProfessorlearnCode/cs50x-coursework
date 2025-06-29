import csv
import sys as s


def main():

    # TODO: Check for command-line usage
    if len(s.argv) != 3:
        print("Usage: python dna.py database sequences")
        return 1

    if not (s.argv[1].endswith('.csv') and s.argv[2].endswith('.txt')):
        print("Error: Invalid file")
        return 2
    else:
        database = s.argv[1]
        sequences = s.argv[2]


    # TODO: Read database file into a variable
    db_load = open(f"{database}", 'r')
    db_obj = csv.reader(db_load)


    # TODO: Read DNA sequence file into a variable
    seq_load = open(f"{sequences}", 'r')
    seq_obj = csv.reader(seq_load)


    # TODO: Find longest match of each STR in DNA sequence
    subsequences = []
    for sequences in db_obj:
        for seq in sequences:
            subsequences.append(seq)
        break

    sequence = []
    for seq in seq_obj:
        sequence = seq
        break


    longest_run = []
    for run in subsequences[1:]:
        longest_run.append(str(longest_match(sequence[0], run)))




    # TODO: Check database for matching profiles
    people = []
    for data in db_obj:
        people.append(data)


    for person in people:
        if person[1:] == longest_run:
            print(person[0])
            break
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

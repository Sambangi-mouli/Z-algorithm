def get_z_array(s):
    z = [0] * len(s)
    left, right, k = 0, 0, 0
    for i in range(1, len(s)):
        if i > right:
            left = right = i
            while right < len(s) and s[right] == s[right - left]:
                right += 1
            z[i] = right - left
            right -= 1
        else:
            k = i - left
            if z[k] < right - i + 1:
                z[i] = z[k]
            else:
                left = i
                while right < len(s) and s[right] == s[right - left]:
                    right += 1
                z[i] = right - left
                right -= 1
    return z

def search(text, pattern, output_file):
    concat = pattern + "$" + text
    z = get_z_array(concat)
    found = False
    pattern_length = len(pattern)

    with open(output_file, 'w') as f:
        for i in range(len(z)):
            if z[i] == pattern_length:
                f.write(f"Pattern found at index {i - pattern_length - 1}\n")
                found = True
        if not found:
            f.write("Pattern not found.\n")

def main():
    try:
        with open("filename.txt", 'r') as text_file, open("patternfile.txt", 'r') as pattern_file:
            text = text_file.read().strip()
            pattern = pattern_file.read().strip()
        
        search(text, pattern, "output.txt")
        
    except FileNotFoundError as e:
        print("Error opening files:", e)

if __name__ == "__main__":
    main()


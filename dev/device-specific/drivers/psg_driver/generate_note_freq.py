"""
A script to generate a C header file with musical note frequency definitions.

This script calculates note frequencies based on the A4=440Hz standard
using the equal temperament tuning system. It then formats these frequencies
as integer #defines in a C header file.
"""

# --- Configuration ---
OUTPUT_FILENAME = "note_freq.h"
A4_FREQ = 440.0
NOTES = ["C", "CS", "D", "DS", "E", "F", "FS", "G", "GS", "A", "AS", "B"]
FLAT_ALIASES = {
    "AS": "BB",
    "CS": "DB",
    "DS": "EB",
    "FS": "GB",
    "GS": "AB"
}
# Note map: steps from A in the same octave
NOTE_STEPS_FROM_A = {"C": -9, "CS": -8, "D": -7, "DS": -6, "E": -5, "F": -4,
                     "FS": -3, "G": -2, "GS": -1, "A": 0, "AS": 1, "B": 2}

def get_frequency(note_name, octave):
    """Calculates the frequency of a note in a given octave."""
    # Calculate the number of half-steps away from A4
    octave_diff = octave - 4
    n_steps = NOTE_STEPS_FROM_A[note_name] + (octave_diff * 12)
    
    # Apply the equal temperament formula: f = f0 * (2^(1/12))^n
    frequency = A4_FREQ * (2.0**(1.0/12.0))**n_steps
    return int(round(frequency))

def generate_header_content():
    """Generates the full content of the musical_notes.h file."""
    lines = []
    
    # --- Header Guard and Comments ---
    lines.append("#ifndef NOTE_FREQ_H_")
    lines.append("#define NOTE_FREQ_H_")
    lines.append("")

    # --- Generate Note Definitions ---
    for octave in range(1, 7): # From Octave 1 to 6
        if octave > 0:
            lines.append(f"// --- Octave {octave} ---")
        
        start_note_index = 9 if octave == 1 else 0 # Octave 1 starts at 'A'
        
        for i in range(start_note_index, len(NOTES)):
            note = NOTES[i]
            freq = get_frequency(note, octave)
            # Pad the frequency for alignment
            lines.append(f"#define NOTE_{note}{octave}    {freq}")
        lines.append("")

    # --- Generate Flat Aliases ---
    lines.append("// --- Aliases for Flats ---")
    for octave in range(1, 7):
        start_note_index = 9 if octave == 1 else 0
        for i in range(start_note_index, len(NOTES)):
            note = NOTES[i]
            if note in FLAT_ALIASES:
                flat_name = FLAT_ALIASES[note]
                lines.append(f"#define NOTE_{flat_name}{octave}   NOTE_{note}{octave}")
                
    lines.append("")
    lines.append("#endif /* NOTE_FREQ_H_ */")
    lines.append("")
    
    return "\n".join(lines)

def main():
    """Main function to generate and write the file."""
    print(f"Generating {OUTPUT_FILENAME}...")
    content = generate_header_content()
    print(content)
    try:
        with open(OUTPUT_FILENAME, "w") as f:
            f.write(content)
        print(f"Successfully wrote to {OUTPUT_FILENAME}")
    except IOError as e:
        print(f"Error writing to file: {e}")

if __name__ == "__main__":
    main()

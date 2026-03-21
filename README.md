# EDLIN - A Historical Re-creation in C
My C99 implementation of the venerable PC/MS-DOS multi-modal, line-orientated, text editor - EDLIN.
```
© Jeremy Simon Thornton 2025
```

## Synopsis
EDLIN was developed in 1980 by Tim Paterson for Seattle Computer Products' QDOS 0.1. When Paterson sold the operating system to Microsoft, EDLIN was included as a temporary solution—intended to last about six months. By virtue of its sheer utility, it persisted as the standard text editor until MS-DOS 4.01, surviving for nearly 11 years until the release of MS-DOS 5.0. During that time, despite various language localizations, it was never significantly updated or overhauled.

## Why recreate EDLIN?
When I first decided to implement my own version of EDLIN, I presumed I was taking on a simple programming exercise—a chance to cut my teeth on tokenizing and parsing techniques with what I assumed would be a straightforward DOS relic. How wrong I was. Further, I learned that the infamous "incorrect DOS version" was not a bug - it was a feature.

What began as a parsing challenge quickly transformed into a journey through computing history and a masterclass in elegant software design. EDLIN, Microsoft's first text editor from 1981, revealed itself to be anything but simple. Beneath its minimalist interface lay a remarkably sophisticated tool built with astonishing efficiency, shaped by the computing constraints of its era.

## The Frenzy of the First MS-DOS
The story of "Big Blue" agreeing with a scrappy young company called Microsoft to produce an operating system for its new computer, the IBM PC—before Bill Gates even had a finished product—has taken its place in computing legend. Part of that legend is EDLIN.

EDLIN had to operate within brutal constraints: 64KB of memory, 4.77MHz processors, and no modern parsing libraries. Yet it managed to deliver a powerful mulit-modal, line-editing experience with context-aware parsing, relative addressing, and a complex command syntax that would challenge any developer to implement cleanly.

Running the 86-DOS emulator on an IBM PC with DOS 3.1 as a reference, I began using EDLIN firsthand. The programming challenges emerged quickly. I dug into EDLIN's command structure—the mix of `[parameters]COMMAND` and `COMMAND[parameters]` patterns, the elegant handling of optional arguments, and the clever use of context that made it so much more than a simple editor. This wasn't just a primitive tool; it was a beautifully designed system that enabled efficient text manipulation through a concise, expressive mini-language.

## EDLIN Functionality: A Multi-Modal Editing Experience
Delving into EDLIN reveals its powerful command syntax. This wasn't a system built on a single, rigid grammar rule. Instead, it employed several distinct syntactic patterns, each elegantly matched to the prevailing use-case and task at hand — writing and editing computer programs. The command syntax enables the editor to shift between distinct modes: command input, mini-editor, text insertion, and interactive search/replace-each optimized for a specific editing task. This multi-modal design is the key to its power and efficiency.

### 1. Command Mode: The Primary Interface
Upon startup, EDLIN awaits commands. This mode follows a sophisticated yet intuitive syntax for manipulating text.

+ Simple Commands: Single-character commands execute immediately, such as:

  + `E` (End Edit & Save)

  + `Q` (Quit without Saving)

  + `?` (Help)

+ "Select, Then Act" Commands: The core editing logic uses a `[range]COMMAND`pattern. This natural flow involves specifying a line number range first, then the action to perform on it.

  + `10,20L` lists lines 10 through 20.

  + `,20D` deletes from the current line (a convenient default) to line 20.

+ Hybrid Search/Replace Commands: For commands requiring additional input, the grammar expands to [range][?]COMMAND[text]. The parser's sophistication allows for flexible combinations:

  + `Stex`t performs a raw search from the current line.

  + `1,100?Rold,new` performs an interactive replace (?) across a defined range, replacing old with new.

### 2. Insert Mode: Adding New Text
Commands like `I` (Insert) and their hybrid pattern, `[line]I`, act as a bridge. They accept a single starting line number before transitioning the editor from Command Mode into Insert Mode. In this state, the user enters text line-by-line. Exiting is done by entering a single period . on an empty line and pressing Enter (a convention adopted from FreeDOS, replacing the original Ctrl-C).

### 3. Line Edit Mode: The Single-Line Mini-Editor
The most fascinating modal shift occurs when you enter a line number alone (e.g., 15). This enters _Line Edit Mode_, a powerful single-line editor controlled by function and control keys.

+ The current line's text is displayed and becomes the _template_.

+ Function Keys (F1-F4) are used to copy characters from the template onto the new line.

+ The Insert (Ins) key toggles between overwriting and inserting characters into the new line.

+ The Escape (Esc) key cancels all edits, restoring the original line.

+ Pressing Enter finalizes the edits, incorporating any changes made using the function keys and insert mode.

### 4. Memory Management Commands: A Testament to Hardware Constraints
Some commands reveal the brutal memory limitations of the early 1980s. The A (Append) command is a prime example. It was not for adding typed content, but for loading the next segment of a file from disk into RAM. When a file was too large for the 64KB memory limit, EDLIN would only load a portion. `[#lines]A` was a memory management tool, appending the next block of the file from disk to make it editable.

### 5. The "Incorrect DOS Version" Debacle: Redeeming Tim Paterson's Design
One of EDLIN's most infamous quirks was its stubborn refusal to run on DOS versions other than the one it was shipped with, displaying the frustrating "Incorrect DOS version" error. Through implementing EDLIN myself, I've come to understand this wasn't poor engineering—it was necessary survival in an era of rapidly evolving system internals. Paterson's EDLIN was highly optimised to work within severe hardware constraints of the early IBM PC system. Unfortunately, this engineering pragmatism of system-level optimizations bound EDLIN to the version of DOS that it came with. Therefore, the decision to validate the execution environment was the responsible choice. The alternative would have been mysterious crashes and corrupted files when EDLIN encountered unexpected system layouts.

## Implementation notes



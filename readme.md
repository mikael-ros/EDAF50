# Exercises and solutions for EDAF50 C++ Programming
These are my personal solutions to the exercises and exams for the EDAF50 C++ Programming course, as it was in spring 2026. This repository also contains my reasoning, usually located in the ``readme.md`` file of the respective folders. Similarly, the original questions (see "Permission"), as they were worded in spring 2026, are included as ``original/readme.md`` in each respective folder, along with their untouched source files and original given solutions (to compare with).

Obviously, it should be noted that these are the ramblings of someone learning C++. Some of the solutions may be misguided. It is available for reference purposes.

This repository is associated with my [Notion database](https://mikaelrr.notion.site/Shared-Notes-Hub-D-C-LTH-f2a47297b9b146dba372e02c4f789d55?source=copy_link).

## Finished exercises
- [x] [Exercise 1 (done 2026-05-26)](Exercise%201/readme.md)
- [x] [Exercise 2 (done 2026-05-26)](Exercise%202/readme.md)
- [x] [Exercise 3 (done 2026-05-27)](Exercise%203/readme.md)
- [x] [Exercise 4 (done 2026-05-28)](Exercise%204/readme.md)
- [ ] Exercise 5
- [ ] Exercise 6

## Finished exams
- [ ] 2025-06-03 (done )

## How to use
There are two ways to use this repository:
1. Use the solutions as reference
2. Fork the repository, remove or move my solutions (files and the answer texts), and use the repository as a template for your own exercises

    You could, for example, run something like:
    ```sh
    find root -type d | while read -r dir; do
        mkdir -p "$dir/mikael-solutions"
        find "$dir" -maxdepth 1 -type f -exec mv {} "$dir/mikael-solutions/" \;
    done
    ```

## Permission

Permission was granted to me, to use and publish the exercises and my solutions was granted by Sven Robertz 4th February 2026. There may also be another set of solutions on the official course page (currently Canvas), if nothing changes.

However, it is not clear what license is associated with the files, if any. 
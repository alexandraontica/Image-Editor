#include <stdio.h>

/**
 * @brief Prints a formatted list of commands and their descriptions to the console.
 *
 * This function prints a table of available commands for interacting with images,
 * including their parameters and descriptions. Each command is displayed with its
 * associated details to guide the user on how to use them effectively.
 */
void print_commands() {
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("| Command Name |        Parameters       |                        Description                        |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      e       |            -            |                 Exit - closes the program                 |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      l       |         N M path        |   Load - loads the image of size NxM from the given path  |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      s       |        index path       |           Save - saves the image from the index           |\n");
    printf("|              |                         |                   at the specified path                   |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      ah      |          index          |    Apply Horizontal Flip - applies the horizontal flip    |\n");
    printf("|              |                         |         operation to the image at the given index         |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      av      |          index          |      Apply Vertical Flip - applies the vertical flip      |\n");
    printf("|              |                         |         operation to the image at the given index         |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|     arl      |          index          |    Apply Rotate Left - rotates to the left the image at   |\n");
    printf("|              |                         |                      the given index                      |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|     arr      |          index          |   Apply Rotate Right - rotates to the right the image at  |\n");
    printf("|              |                         |                      the given index                      |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      ac      | index x y width height  |          Apply Crop - applies the crop operation          |\n");
    printf("|              |                         | with the given parameters to the image at the given index |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      ae      |  index rows cols R G B  |        Apply Extend - applies the extend operation        |\n");
    printf("|              |                         | with the given parameters to the image at the given index |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      ap      | index_dst index_src x y |         Apply Paste - applies the paste operation         |\n");
    printf("|              |                         |  with the given parameters to the image at the index_dst  |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      cf      |  size [list of values]  |   Create Filter - creates a filter of the given size with |\n");
    printf("|              |                         |     the given list of values (example: if creating a      |\n");
    printf("|              |                         |     filter of size 3, then 9 values will follow size)     |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      af      |  index_img index_filter |    Apply Filter - applies the filter from index_filter    |\n");
    printf("|              |                         |                 to the image at index_img                 |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      df      |       index_filter      |  Delete Filter - deletes the filter from index_filter     |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
    printf("|      di      |        index_img        |      Delete Image - deletes the image from index_img      |\n");
    printf("+--------------+-------------------------+-----------------------------------------------------------+\n");
}

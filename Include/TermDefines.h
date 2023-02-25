//
// Created by piotrmiszta on 24.02.23.
//

#ifndef PROCESSES_TERMDEFINES_H
#define PROCESSES_TERMDEFINES_H
#define uint                    unsigned int
#define BLACK		            "\033[30m"
#define DARK_RED 		        "\033[31m"
#define DARK_GREEN		        "\033[32m"
#define DARK_YELLOW     		"\033[33m"
#define DARK_BLUE		        "\033[34m"
#define DARK_MAGENTA		    "\033[35m"
#define DARK_CYAN		        "\033[36m"
#define LIGHT_GRAY		        "\033[37m"
#define DARK_GRAY		        "\033[90m"
#define RED		                "\033[91m"
#define GREEN	        	    "\033[92m"
#define ORANGE		            "\033[93m"
#define BLUE		            "\033[94m"
#define MAGENTA		            "\033[95m"
#define CYAN		            "\033[96m"
#define WHITE		            "\033[97m"
#define RESET                   "\x1B[0m"

#define P_BLACK		                printf("\033[30m")
#define P_DARK_RED 		            printf("\033[31m")
#define P_DARK_GREEN		        printf("\033[32m")
#define P_DARK_YELLOW     		    printf("\033[33m")
#define P_DARK_BLUE		            printf("\033[34m")
#define P_DARK_MAGENTA		        printf("\033[35m")
#define P_DARK_CYAN		            printf("\033[36m")
#define P_LIGHT_GRAY		        printf("\033[37m")
#define P_DARK_GRAY		            printf("\033[90m")
#define P_RED		                printf("\033[91m")
#define P_GREEN	        	        printf("\033[92m")
#define P_ORANGE		            printf("\033[93m")
#define P_BLUE		                printf("\033[94m")
#define P_MAGENTA		            printf("\033[95m")
#define P_CYAN		                printf("\033[96m")
#define P_WHITE		                printf("\033[97m")
#define P_RESET                     printf("\x1B[0m")
/*
 * SPECIAL KEYS LIKE ^[<N>A
 */
#define DEL_LINE                printf("\33[A")
#define DEL_X_LINES(g)          printf("\33[%dA", g)

#endif //PROCESSES_TERMDEFINES_H

#include <stdio.h>
#include <string.h>
#include "funcs.h"

// Interpreter for Volite

typedef struct Lexer{
	char LBRACKET;
	char RBRACKET;
	char QUOTE;
	const char *keyword_OUT;
	int LBRACKET_STATE;
	int RBRACKET_STATE;
	int BRACKET_STATE;
	int QUOTE_STATE;

} Lexer;

void parser(const char *src, Lexer *lexer){
	// searching for keywords
	char keyword[10];
	int it = 0;
	int keyword_found = 0;
	for(int i = 0; i < strlen(src); i++){
		if(src[i] != lexer->LBRACKET && src[i] != lexer->RBRACKET && src[i] != lexer->QUOTE && src[i] != ' '){
			keyword[it++] = src[i];
		}
		if(strcmp(keyword, lexer->keyword_OUT) == 0){
			printf("KEYWORD: %s found\n", lexer->keyword_OUT);
			keyword_found = 1;
			break;
		}
	}
	// vars for brackets
	int lbracket_pos = 0;
	int rbracket_pos = 0;

	// searching for brackets and qoutes
	for(int i = 0; i < strlen(src); i++){
		if(src[i] == lexer->LBRACKET){
			lexer->LBRACKET_STATE = 1;
			lbracket_pos = i;
		}
		if(src[i] == lexer->RBRACKET){
			lexer->RBRACKET_STATE = 1;
			rbracket_pos = i;
		}
	}

	// vars for quotes
	int quote_found = 0;
	int all_quotes_found = 0;

	for(int i = 0; i < strlen(src); i++){
		if(src[i] == lexer->QUOTE && quote_found){
			all_quotes_found = 1;
		}
		if(src[i] == lexer->QUOTE){
			quote_found = 1;
		}
	}

	// check brackets state

	if(all_quotes_found){
		printf("\nQUOTES WERE FOUND AND CLOSED\n");
		lexer->QUOTE_STATE = 1;
	}
	else{
		if(quote_found){
			printf("\nONE QUOTE %c missing\n", lexer->QUOTE);
		}
	}

	// check quote state
	
	if(lexer->LBRACKET_STATE && lexer->RBRACKET_STATE){
		printf("\nBRACKETS WERE FOUND AND CLOSED\n");
		lexer->BRACKET_STATE = 1;
	}
	else{
		if(!lexer->LBRACKET_STATE){
			printf("\nBRACKET %c was not closed\n", lexer->LBRACKET);
		}
		if(!lexer->RBRACKET_STATE){
			printf("\nBRACKET %c was not closed\n", lexer->RBRACKET);
		}
	}

	printf("\n--CURRENT STATE-- :: BRACKETS: %d | QUOTE: %d | KEYWORD: %d | \n", lexer->BRACKET_STATE,
																			  lexer->QUOTE_STATE,
																			  keyword_found);

	if(lexer->QUOTE_STATE == 1 && lexer->BRACKET_STATE == 1 && keyword_found == 1){
		printf("\nOutput: \n\n");
		for(int i = lbracket_pos + 2; i < rbracket_pos - 1; i++){
			printf("%c", src[i]);
		}
	}

}

int main(int argc, char **argv){
	Lexer lexer;
	lexer.LBRACKET = '(';
	lexer.RBRACKET = ')';
	lexer.QUOTE = '"';
	lexer.keyword_OUT = "out";
	lexer.LBRACKET_STATE = 0;
	lexer.RBRACKET_STATE = 0;

	char file_buf[100];
	int it = 0;
	int new_line = 0;
	int index = -1;
	int comment_found = 0;

	// read file
	FILE *file = fopen(argv[1], "r");
	if(file != NULL){
		if(ext_vol(argv[1])){
			while(!feof(file)){
				file_buf[it++] = fgetc(file);
			}
			file_buf[it] = '\0';

			printf("\n\nSOURCE CODE: \n%s\n", file_buf);

			parser(file_buf, &lexer);
		}
		else{
			printf("A (.vol) file needed\n");
		}
	}
	else{
		printf("ERROR: File open error\n");
	}

	return 0;
}

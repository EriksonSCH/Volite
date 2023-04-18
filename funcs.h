#include <string.h>

int find_key(const char *src, const char *str, int get_end){
	int j = 0;
	int len = 0;
	int loc = 0;
	char buf[100];
	
	int space = 0;
	int failed = 0;

	for(int i = 0; src[i] != ' '; i++){
		loc++;
		if(strcmp(buf, str) == 0){
			break;
		}
		if(src[i] == str[j]){
			buf[j] = src[i];
			j++;
			len++;
		}
		else{
			j = 0;
			len = 0;
			memset(buf, 0, sizeof(buf));
		}
	}
	buf[j] = '\0';

	for(int i = 0; i < strlen(src); i++){
		if(src[i] == ' '){
			space = 1;
			break;
		}
	}

	if(space){
		for(int i = 0; src[i] != ' '; i++){
			if(buf[i] != str[i]){
				failed = 1;
			}
		}
		if(!failed){
			if(get_end){
				return loc;
			}
			loc -= strlen(str);
			return loc;
		}
	}

	else{
		if(strcmp(buf, str) == 0){
			if(get_end){
				return loc;
			}
			loc -= strlen(str);
			return loc;
		}
	}
}

int find_space(const char *src){
	int i;
	for(i = 0; src[i] != ' '; i++);
	return i;
}

int find(const char *src, char c){
	int i;
	for(i = 0; i < strlen(src); i++){
		if(src[i] == c){
			return i;
		}
	}
	return -1;
}

int rfind(const char *src, char c){
	int i;
	for(i = strlen(src); i != 0; i--){
		if(src[i] == c){
			return i;
		}
	}
	return -1;
}

int ext_vol(const char *path){
	char tmp[10];
	int it = 0;

	for(int i = rfind(path, '.'); i < strlen(path); i++){
		tmp[it++] = path[i];
	}
	tmp[it] = '\0';

	if(strcmp(tmp, ".vol") == 0){
		return 1;
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct letter{
    char value;
    int frequence;
    char code[9];
    struct letter *right;
    struct letter *left;
    int digit;
    int counter;
    int flag;
};
char* open_file(struct letter **base, int *base_size, int *converted_size);
struct letter* build_tree(struct letter *leafs, int *tree_size);
int find_min(struct letter *a, int a_size, int *first_min, int *second_min);
void create_code(struct letter *node, char cod[]);
void convert_text(struct letter *data_set, int set_size, char *bare, int bare_size);

int main(void){
    struct letter *data;
	int data_size, binary_size, size;
	char *binary_text;
	binary_text=open_file(&data, &data_size, &binary_size);
	
	size=data_size;
	struct letter *root = build_tree(data, &size);
	
	if(size>1){
		for (int i = 0; i < size; i++) {
	        if (root[i].flag == 0) {
	            create_code(&root[i], "\0");
	    	}
    	}
	}else if(size==1){
		root[0].code[0]='0';
	}
	
    for (int i = 0; i < data_size; i++) {
        for(int j=0; j<size; j++){
        	if (root[j].value == data[i].value && root[j].value!='\0') {
            	data[i]=root[j];
        	}
		}
    }
    for(int i=0;i<data_size; i++){
    	printf("%c**%d***%s{%d}\n", data[i].value, data[i].frequence, data[i].code, data[i].digit);
	}
    printf("%s" ,binary_text);

	convert_text(data, data_size, binary_text, binary_size);
	
	free(data);
    free(binary_text);
    return 0;
}
void create_code(struct letter *node, char cod[]) {
	
	if(node->flag==0){
		node->code[0]='\0';
	}else{
		strcat(node->code, cod);
		node->digit=strlen(node->code);
	}

    if (node->left != NULL) {
        strcpy(node->left->code, node->code);
        create_code(node->left, "0");
    }
    if (node->right != NULL) {
        strcpy(node->right->code, node->code);

        create_code(node->right, "1");
    }
    
	return;
}
int find_min(struct letter *a, int a_size, int *first_min, int *second_min) {
    int end = 1;
    *first_min = a_size - 1;
    for (int i = 0; i < a_size; i++) {
        if (a[i].flag == 0 && a[i].frequence < a[*first_min].frequence) {
            *first_min = i;
        }
    }
    a[*first_min].flag = 1;
    for (int i = 0; i < a_size; i++) {
        if (a[i].flag == 0) {
            *second_min = i;
            end = 0;
            break;
        }
    }
    if (end) {
        return 0;
    }
    for (int i = 0; i < a_size; i++) {
        if (a[i].flag == 0 && a[i].frequence < a[*second_min].frequence) {
            *second_min = i;
        }
    }
    a[*second_min].flag = 1;
    return 1;
}
struct letter* build_tree(struct letter *leafs, int *tree_size) {
	
    struct letter *main_tree = (struct letter *)malloc(*tree_size * 2 * sizeof(struct letter));
    if (!main_tree) {
        perror("Memory allocation failed  main tree");
        return NULL;
    }

    for (int i = 0; i < (*tree_size) * 2; i++) {
        main_tree[i].code[0] = '\0';
        main_tree[i].left = NULL;
        main_tree[i].right = NULL;
        main_tree[i].flag = 0;
        main_tree[i].value = '\0';
        main_tree[i].frequence = 0;
        main_tree[i].digit=0;
        main_tree[i].counter=0;
    }
    
    main_tree = leafs;
    int min1, min2 ;
    while (find_min(main_tree, *tree_size, &min1, &min2)) {
        main_tree[*tree_size].left = &main_tree[min1];
        main_tree[*tree_size].right = &main_tree[min2];
        main_tree[(*tree_size)++].frequence = main_tree[min1].frequence + main_tree[min2].frequence;
    }
    
    main_tree[min1].flag = 0;
    return main_tree;
}

char* open_file(struct letter **base, int *base_size, int *converted_size) {
    *base = (struct letter *)malloc(999999 * sizeof(struct letter));
    if (!(*base)) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen("output.txt", "rb");
    if (!in) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    *base_size = 0;
    while (fscanf(in, "%d%c", &(*base)[*base_size].frequence, &(*base)[*base_size].value) == 2) {
    	if((*base)[*base_size].frequence==0){
        	break;
		}
        (*base)[*base_size].code[0] = '\0';
        (*base)[*base_size].right = NULL;
        (*base)[*base_size].left = NULL;
        (*base)[*base_size].flag = 0;
        (*base)[*base_size].digit = 0;
        (*base)[*base_size].counter = 0;
        (*base_size)++;
        
    }

    *base = (struct letter *)realloc(*base, (*base_size) * sizeof(struct letter));
    if (!(*base)) {
        perror("Memory allocation failed during realloc");
        exit(EXIT_FAILURE);
    }

    unsigned char x;
    char *code_arr = (char *)malloc(99999 * sizeof(char));
    if (!(code_arr)) {
        perror("Memory allocation failed during code_arr malloc");
        exit(EXIT_FAILURE);
    }
    
    int syc = 0, *bin = (int *)malloc(99999 * sizeof(int));

    while (fread(&x, sizeof(unsigned char), 1, in) == 1) {
    	if(x=='\n'){
		}else{
			bin[syc] = x;
        	syc++;
		}
        
    }

    for (int i = 0; i < syc; i++){
        int temp = bin[i];
        for (int j = 7; j >= 0; j--) {
        	
	        if(temp%2==1){
	        	code_arr[j+(8*i)]='1';
	        	temp/=2;
			}else if(temp%2==0){
				code_arr[j+(8*i)]='0';
				temp/=2;
			}
	    }
    }
	
    *converted_size = syc * 8;
    code_arr=(char*)realloc(code_arr, (*converted_size)*sizeof(char));
    if (!(code_arr)) {
        perror("Memory allocation failed during code_arr realloc");
        exit(EXIT_FAILURE);
    }
   
	printf("\n");
    free(bin);
    fclose(in);

    return code_arr;
}

void convert_text(struct letter *data_set, int set_size, char *bare, int bare_size) {
	
	if (data_set == NULL || bare == NULL || set_size <= 0 || bare_size <= 0) {
        fprintf(stderr, "Invalid input parameters\n");
        return;
    }
    char *converted = (char*)malloc(bare_size * sizeof(char)); 
    if (!converted) {
        fprintf(stderr, "Memory allocation failed\n");
        return ;
    }
    int c_size = 0;
    int index = 0, cont=1;
    
    while(index < bare_size && cont){
    	
   		for(int i=0; i<set_size; i++){
    		if(strncmp(&bare[index], data_set[i].code, data_set[i].digit)==0){
    			if(data_set[i].counter<data_set[i].frequence){
                    (data_set[i].counter)++;
                    converted[c_size++]=data_set[i].value;
                    index+=(data_set[i].digit);
                    break;
                }
			}
		}
	
		cont=0;
        for(int i=0;i<set_size;i++){
            if(data_set[i].counter<data_set[i].frequence){
                cont=1;
            }
        
		}
		
	}
		printf("\n%d", c_size);
    for(int i=0; i<set_size; i++){
    	c_size+= data_set[i].frequence;
	}	
    converted = (char*)realloc(converted, c_size * sizeof(char));
    if (!converted) {
        fprintf(stderr, "Memory reallocation failed\n");
        return;
    }
    converted[c_size]='\0';
    printf("\n%s ",converted);
    
    FILE *final;
    final=fopen("last.txt", "w");
   	fprintf(final, "%s\n", converted);

	
    fclose(final);

    return ;
}


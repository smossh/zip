#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct huf_node {
    char val;
    int fre;
    char code[300];
    struct huf_node *right;
    struct huf_node *left;
    int flag;
};

int find_min(struct huf_node *a, int a_size, int *first_min, int *second_min);
struct huf_node* build_tree(struct huf_node *leafs, int *tree_size);
void create_code(struct huf_node *node, char cod[]);
char* convert_binary(struct huf_node *values, int value_size, char *text, int bare_size, int *converted_size);
void print(char *base_unit, int base_size, struct huf_node *last_tree, int last_size);


int main(void) {
    FILE *ptr = fopen("input.txt", "r");
    if (ptr == NULL) {
        perror("Failed to open file");
        return 1;
    }
    struct huf_node *base = (struct huf_node *)malloc(256 * sizeof(struct huf_node));
    if (!base) {
        perror("Memory allocation failed base");
        fclose(ptr);
        return 1;
    }
    char *bare_text = (char *)malloc(9999999 * sizeof(char));
    if (!bare_text) {
        perror("Memory allocation failed bare_text");
        free(base);
        fclose(ptr);
        return 1;
    }

    int text_size = 0;
    int size = 0, fl = 0;

    while (fscanf(ptr, "%c", &bare_text[text_size]) == 1) {
        if (bare_text[text_size] != '\n') {
            fl = 0;
            for (int i = 0; i < size; i++) {
                if (base[i].val == bare_text[text_size]) {
                    base[i].fre++;
                    fl = 1;
                    break;
                }
            }
            if (!fl) {
                base[size].val = bare_text[text_size];
                base[size++].fre = 1;
            }
        }
        text_size++;
    }
    

    bare_text = (char*)realloc(bare_text, text_size * sizeof(char));
    base = (struct huf_node*)realloc(base, size * sizeof(struct huf_node));
    if (!base||!bare_text) {
        perror("Memory allocation failed");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        base[i].code[0] = '\0';
        base[i].left = NULL;
        base[i].right = NULL;
        base[i].flag = 0;
    }
    struct huf_node *tree = build_tree(base, &size);
 	
    if (!tree) {
        perror("Memory allocation failed");
        return 1;
    }
    if(size!=1){
    	for (int i = 0; i < size; i++) {
	        if (tree[i].flag == 0) {
	            create_code(&tree[i], "\0");
	        }
    	}
	}else{
		tree[0].code[0]=0;
	}
   

    int base_size = 0;
    for (int i = 0; i < size; i++) {
        if (tree[i].val == base[base_size].val && tree[i].val!='\0') {
            base[base_size++]=tree[i];
        }
    }
    for(int i=0; i<base_size; i++){
    	printf("%c^^%d^^^%s{%d}\n", base[i].val, base[i].fre, base[i].code, base[i].flag);
	}
    
	
    int binary_size=0;
    char *binary_arr=convert_binary(base, base_size, bare_text, text_size, &binary_size);
    printf("Binary text: ");
    printf("%s", binary_arr);
    print(binary_arr, binary_size, base, base_size);
    
    return 0;
}

int find_min(struct huf_node *a, int a_size, int *first_min, int *second_min) {
    int end = 1;
    *first_min = a_size - 1;
    for (int i = 0; i < a_size; i++) {
        if (a[i].flag == 0 && a[i].fre < a[*first_min].fre) {
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
        if (a[i].flag == 0 && a[i].fre < a[*second_min].fre) {
            *second_min = i;
        }
    }
    a[*second_min].flag = 1;
    return 1;
}

struct huf_node* build_tree(struct huf_node *leafs, int *tree_size) {
	
    struct huf_node *main_tree = (struct huf_node *)malloc(*tree_size * 2 * sizeof(struct huf_node));
    if (!main_tree) {
        perror("Memory allocation failed  main tree");
        return NULL;
    }

    for (int i = 0; i < (*tree_size) * 2; i++) {
        main_tree[i].code[0] = '\0';
        main_tree[i].left = NULL;
        main_tree[i].right = NULL;
        main_tree[i].flag = 0;
        main_tree[i].val = '\0';
        main_tree[i].fre = 0;
    }
    main_tree = leafs;
    int min1 , min2 ;

    while (find_min(main_tree, *tree_size, &min1, &min2)) {
        main_tree[*tree_size].left = &main_tree[min1];
        main_tree[*tree_size].right = &main_tree[min2];
        main_tree[(*tree_size)++].fre = main_tree[min1].fre + main_tree[min2].fre;
    }
    main_tree[min1].flag = 0;
    return main_tree;
}

void create_code(struct huf_node *node, char cod[]) {
	if(node->flag==0){
		node->code[0]='\0';
	}else{
		strcat(node->code, cod);
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

char* convert_binary(struct huf_node *values, int value_size, char *text, int bare_size, int *converted_size) {
    char *converted_arr = (char *)malloc(9999999 * sizeof(char));
    if (!converted_arr) {
        perror("Memory allocation failed coverted array");
        return NULL;
    }
    converted_arr[0] = '\0';
    
    if(value_size==1){
    	for(int i=0; i<bare_size; i++){
    		converted_arr[i]='0';
		}
	}else{
		for (int i = 0; i < bare_size; i++) {
	        for (int j = 0; j < value_size; j++) {
	            if (text[i] == values[j].val) {
	            	strcat(converted_arr, values[j].code);
	            }
	        }
    	}
	}
    *converted_size =strlen(converted_arr);
    while (*converted_size % 8 != 0) {
        converted_arr[(*converted_size)++] = '1';
    }
    converted_arr = (char *)realloc(converted_arr, (*converted_size) * sizeof(char));
    if (!converted_arr) {
        perror("Memory allocation failed converted_arr realloc");
        return NULL;
    }
	
    return converted_arr;
}
void print(char *base_unit, int base_size, struct huf_node *last_tree, int last_size){

    FILE *son = fopen("output.txt", "w");
    
    if (!son) {
        perror("Failed to open file for writing");
        return ;
    }
    for(int i=0; i<last_size; i++){
    	fprintf(son,"%d%c", last_tree[i].fre, last_tree[i].val);
	}
	fprintf(son, "00\n");
	
    unsigned char last = 0;
	for(int i=0;i<base_size;i+=8){
       	last=0;
		if(base_unit[i]=='1'){
            last|=128;
        }
        if(base_unit[i+1]=='1'){
            last|=64;
        }
        if(base_unit[i+2]=='1'){
            last=last|32;
        }
    	if(base_unit[i+3]=='1'){
            last|=16;
        }
        if(base_unit[i+4]=='1'){
            last|=8;
        }
        if(base_unit[i+5]=='1'){
            last|=4;
        }
        if(base_unit[i+6]=='1'){
            last|=2;
        }
        if(base_unit[i+7]=='1'){
            last|=1;
        }
        fprintf(son,"%c",last);
    }
         
}

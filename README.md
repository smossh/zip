#include <stdio.h>
#include <stdlib.h>
#include<string.h>


struct ch {
    char origin;
    int fr;
};
struct huf_node {
    char val;
    int fre;
    char code[10000];
    struct huf_node *right;
    struct huf_node *left;
};
struct tree {
    struct huf_node *arr;
};

struct huf_node base(struct ch h) {
    struct huf_node *c = (struct huf_node*) malloc(sizeof(struct huf_node));
    if (!c) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    c->val = h.origin;
    c->fre = h.fr;
    c->code[0] = '\0';
    c->left = NULL;
    c->right = NULL;
    return *c;
}

void sort(struct ch a[], int s_size) {
	
    int control = 1;
    struct ch te;
    for (int l = 0; l < s_size && control; l++) {
        control = 0;
        for (int m = 0; m < s_size - 1; m++) {
            if (a[m].fr > a[m + 1].fr) {
                te = a[m];
                a[m] = a[m + 1];
                a[m + 1] = te;
                control = 1;
            }
        }
    }
    for (int p = 0; p < s_size; p++) {
        printf("%c-%d ", a[p].origin, a[p].fr);
    }
    printf("\n");
    
}

struct tree* build(struct huf_node *b, int b_size, int *a_size, struct huf_node *nodes) {
    struct tree *base = (struct tree*) malloc(sizeof(struct tree));
   
    if (!base) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    base->arr = (struct huf_node*) malloc(b_size * 2 * sizeof(struct huf_node));
    if (!base->arr) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2 * b_size; i++) {
        base->arr[i].code[0] ='\0';
        base->arr[i].fre = 0;
        base->arr[i].left = NULL;
        base->arr[i].right = NULL;
        base->arr[i].val = '\0';
    }
    for (int i = 0; i < b_size; i++) {
        nodes[i].code[0] ='\0';
        nodes[i].fre = 0;
        nodes[i].left = NULL;
        nodes[i].right = NULL;
        nodes[i].val = '\0';
    }
	
	if(b[1].val!='\0'){
		nodes[0].right = &b[1];
	}
    nodes[0].left = &b[0];
    
    
	if(b[1].val!='\0'){
    	nodes[0].fre = b[1].fre + b[0].fre;
	}
	else{
		nodes[0].fre = b[0].fre;
	}
	
	int k=0;
	int n_size=0;
	
	if(b[1].val!='\0'){
		base->arr[1] = b[1];
		base->arr[2] = nodes[0];
		base->arr[0] = b[0];
		k=3;
		n_size=1;
	}else{
		base->arr[0] = b[0];
    	base->arr[1] = nodes[0];
    	n_size=1;
    	k=2;
	}

    for (int i = 2; i < b_size; i++) {
    	
        nodes[n_size].right = &nodes[n_size - 1];
        nodes[n_size].left = &b[i];
        nodes[n_size].fre = nodes[n_size - 1].fre + b[i].fre;

        base->arr[k++] = b[i];
        base->arr[k++] = nodes[n_size];

        n_size++;
    }
    
    *a_size = n_size + b_size;
    
	base->arr = (struct huf_node*) realloc(base->arr, (*a_size) * sizeof(struct huf_node));
    if (!base->arr) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
	//code assigment
    int syc=1;
    if(b[1].val!='\0'){
    	base->arr[(*a_size)-1].code[0]='\0';
	    base->arr[(*a_size)-2].code[0]='0';
	    base->arr[(*a_size)-2].code[1]='\0';
	    base->arr[(*a_size)-3].code[0]='1';
	    base->arr[(*a_size)-3].code[1]='\0';
	}else{
		base->arr[(*a_size)-1].code[0]='\0';
	    base->arr[(*a_size)-2].code[0]='0';
	    base->arr[(*a_size)-2].code[1]='\0';
	}
   	
   	
    for(int i=(*a_size)-3;i>2;i-=2){
    	strcpy(base->arr[i-2].code,base->arr[i].code);
    	base->arr[i-2].code[syc]='1';
    	base->arr[i-2].code[syc+1]='\0';
    	
    	strcpy(base->arr[i-1].code,base->arr[i].code);
    	base->arr[i-1].code[syc]='0';
    	base->arr[i-1].code[syc++]='\0';	
	}


	if(b[1].val!='\0'){
		strcpy(base->arr[0].code,base->arr[2].code);
		base->arr[0].code[syc]='0';
		base->arr[0].code[syc+1]='\0';
		
		strcpy(base->arr[1].code,base->arr[2].code);
	   	base->arr[1].code[syc]='1';
		base->arr[1].code[syc+1]='\0';
	}

    return base;
}

void bit(char base_unit[],int base_size){
	FILE *out;
	out=fopen("output.txt","w");
	unsigned char last=0;
	int fl=0;
	for(int i=0;i<base_size;i+=8){
	
		if(base_unit[i]=='1'){
			last=last|128;
			fl=1;
		}
		if(base_unit[i+1]=='1'){
			last=last|64;
			fl=1;
		}
		if(base_unit[i+2]=='1'){
			last=last|32;
			fl=1;
		}
		if(base_unit[i+3]=='1'){
			last=last|16;
			fl=1;
		}
		if(base_unit[i+4]=='1'){
			last=last|8;
			fl=1;
		}
		if(base_unit[i+5]=='1'){
			last=last|4;
			fl=1;
		}
		if(base_unit[i+6]=='1'){
			last=last|2;
			fl=1;
		}
		if(base_unit[i+7]=='1'){
			last=last|1;
			fl=1;
		}
		if(fl){
			fprintf(out,"%c",last);
		}else{
			fprintf(out,"%u",last);
		}
		
		
		last=0;
 	}
 	
} 

int main() {
    FILE *ptr = fopen("input.txt", "r");
    if (ptr == NULL) {
        perror("Failed to open file");
        return 1;
    }
	printf("%c",0);
    struct ch *st = (struct ch*) malloc(1000 * sizeof(struct ch));
    if (!st) {
        perror("Memory allocation failed");
        fclose(ptr);
        return 1;
    }

    int size = 0, flag = 0;
    char *t=(char*)malloc(100000000*sizeof(char));
	int st_size=0;
	
    while (fscanf(ptr, "%c", &t[st_size]) == 1) {
    	
        flag = 0;
        for (int i = 0; i < size; i++) {
            if (t[st_size] == st[i].origin) {
                st[i].fr++;
                flag = 1;
                break;
            }
        }
        if (!flag) {
            st[size].origin = t[st_size];
            st[size].fr = 1;
            size++;
           
        }
        if(t[st_size]=='\n'){
    		st_size--;
		}
        st_size++;
    }

    st = (struct ch*) realloc(st, size * sizeof(struct ch));
    if (!st) {
        perror("Memory allocation failed");
        fclose(ptr);
        return 1;
    }

    fclose(ptr);
    if(size!=1){
    	sort(st, size);
	}else{
		printf("%c-%d",st[0].origin,st[0].fr);
		st[1].origin=NULL;
		st[1].fr=0;
	}
    
    struct huf_node *node_base = (struct huf_node*) malloc(size * sizeof(struct huf_node));
    struct huf_node *node = (struct huf_node*) malloc(size * sizeof(struct huf_node));
    if (!node_base || !node) {
        perror("Memory allocation failed");
        free(st);
        return 1;
    }

    for (int i = 0; i < size+1; i++) {
        node_base[i] = base(st[i]);
    }

    free(st);
	
    int arr_size;
    
    struct tree *root = build(node_base, size, &arr_size, node);
    char *out_arr;
    out_arr=(char*)malloc(arr_size*9999999*sizeof(char));
    
    for(int i=0;i<st_size;i++){
		for(int j=0;j<arr_size;j++){
			if(t[i]==root->arr[j].val){
				strcat(out_arr,root->arr[j].code);
				break;
			}
		}
	}
	
	free(t);
    arr_size=strlen(out_arr);

    while(arr_size%8!=0){
    	out_arr[arr_size]='1';
    	arr_size++;
    	
	}
	
	out_arr=(char*)realloc(out_arr,arr_size*sizeof(char));
	
	
	bit(out_arr,arr_size);
	
    free(root->arr);
    free(root);
    return 0;
}

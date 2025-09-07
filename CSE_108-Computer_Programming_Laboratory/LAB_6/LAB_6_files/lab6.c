#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef enum {
   PLAINTEXT,
   CIPHERTEXT,
   KEY
} text_type;


char** generate_cipher_array(){
    char** cipher_array = (char**)malloc(sizeof(char*) * 26);
    
    for (int i=0; i <26; i++){
        cipher_array[i] = (char*)malloc(sizeof(char) * 26);
    }
    
    for(int i=0; i<26; i++){
        for(int k=0; k<26; k++){
            cipher_array[i][k] = ((i+k)%26) + 65;
        }
    }
    
    return cipher_array;
}

void print_array(char** cipher_array){

	printf("============================================\n");

    for(int i=0; i<26; i++){
        for(int k=0; k<26; k++){
            printf("%c ", cipher_array[i][k]);
        }
        printf("\n");
	}

	printf("============================================\n");
}

void free_cipher_array(char** cipher_array){
    for(int i = 0; i < 26; i++){
        free(cipher_array[i]); 
    }
    free(cipher_array); 
}

char* get_input_string(text_type type){
   int capacity = 10;
   int length = 0;
   char* str = (char*)malloc(capacity);
   char ch;
   
   if(type == PLAINTEXT){
       printf("Plaintext: ");
   }else if(type == KEY){
	   printf("Key: ");
   }
    else {
       printf("Ciphertext: ");
   }
   
   while((ch = getchar()) != '\n'){
       if(length >= capacity - 1){
           capacity *= 2;
           str = (char*)realloc(str, capacity);
       }
       str[length] = ch;
       length++;
   }
   
   str[length] = '\0';
   return str;
}

int get_length(char* str){
   int length = 0;
   while(str[length] != '\0'){
       length++;
   }
   return length;
}


char* generate_keystream(char* key, int text_length){
   int key_length = get_length(key);
   char* keystream = (char*)malloc(text_length + 1);
   
   for(int i = 0; i < text_length; i++){
	   keystream[i] = key[i % key_length];
   }
   keystream[text_length] = '\0';
   
   return keystream;
}

char* encryption_result(char* plaintext, char* keystream, char** cipher_array){
   int length = get_length(plaintext);
   char* ciphertext = (char*)malloc(length + 1);
   
   for(int i = 0; i < length; i++){
	   int p_index = plaintext[i] - 65;
	   int k_index = keystream[i] - 65;
	   ciphertext[i] = cipher_array[p_index][k_index];
   }
   ciphertext[length] = '\0';
   
   return ciphertext;
}

char* decryption_result(char* ciphertext, char* keystream, char** cipher_array){
   int length = get_length(ciphertext);
   char* plaintext = (char*)malloc(length + 1);
   
   for(int i = 0; i < length; i++){
	   int k_index = keystream[i] - 65;
	   char c = ciphertext[i];
	   int p_index = 0;
	   
	   for(int j = 0; j < 26; j++){
		   if(cipher_array[j][k_index] == c){
			   p_index = j;
			   break;
		   }
	   }
	   plaintext[i] = p_index + 65;
   }
   plaintext[length] = '\0';
   
   return plaintext;
}


int main(){

    printf("Hello World\n");
    char** cipher_array = generate_cipher_array();
    print_array(cipher_array);


	
	// Encryption section

	printf("Please enter the Plaintext and KEY for ENCRYPTION \n");
	char* plaintext = get_input_string(PLAINTEXT);
	char* key_plain = get_input_string(KEY);
	char* keystream_plain = generate_keystream(key_plain, get_length(plaintext));
	printf("Keystram: %s\n", keystream_plain);
	char* ciphertext_plain = encryption_result(plaintext, keystream_plain, cipher_array);
	printf("Ciphertext: %s\n", ciphertext_plain);
	

	// Decryption section

	printf("Please enter the Ciphertext and KEY for DECRYPTION \n");
	char* ciphertext = get_input_string(CIPHERTEXT);
	char* key_cipher = get_input_string(KEY);
	char* keystream_cipher = generate_keystream(key_cipher, get_length(ciphertext));
	printf("Keystram: %s\n", keystream_cipher);
	char* plaintext_cipher = decryption_result(ciphertext, keystream_cipher, cipher_array);
	printf("Plaintext: %s\n", plaintext_cipher);


	free_cipher_array(cipher_array);

	free(plaintext);
	free(ciphertext);
	free(key_plain);
	free(key_cipher);
	free(keystream_plain);
	free(keystream_cipher);
	free(ciphertext_plain);
	free(plaintext_cipher);
	
    
    return 0;
}
// ID:- 202051147
// Name:- Prince Rakholiya
// Lab Assignment 3
// CS364


#include <stdio.h>

// Defining Subbyte table using 16 X 16 matrix where each element is of 8 bit.
unsigned char sub[16][16] = {{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,},
                             {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,},
                             {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,},
                             {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,},
                             {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,},
                             {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,},
                             {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,},
                             {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,},
                             {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,},
                             {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,},
                             {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,},
                             {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,},
                             {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,},
                             {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,},
                             {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,},
                             {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

// Defining 10 R constant using 10 X 4 matrix and we will use this Rcon matrix in Key scheduling
unsigned char Rcon[10][4] = {{0x01, 0x00, 0x00, 0x00}, //Rcon[1]
                             {0x02, 0x00, 0x00, 0x00}, //Rcon[2]
                             {0x04, 0x00, 0x00, 0x00}, //Rcon[3]
                             {0x08, 0x00, 0x00, 0x00}, //Rcon[4]
                             {0x10, 0x00, 0x00, 0x00}, //Rcon[5]
                             {0x20, 0x00, 0x00, 0x00}, //Rcon[6]
                             {0x40, 0x00, 0x00, 0x00}, //Rcon[7]
                             {0x80, 0x00, 0x00, 0x00}, //Rcon[8]
                             {0x1b, 0x00, 0x00, 0x00}, //Rcon[s]
                             {0x36, 0x00, 0x00, 0x00}};//Rcon[10]

// We need 44 words in key scheduling where each word is of 32 bit. So i am store all 44 word in matrix of 44 X 4.
unsigned char words[44][4];


// ROTWORD function for key scheduling 
void rotWord(unsigned char keyTemp[4]){
    unsigned char temp = keyTemp[0]; // keyTemp contain 4 element each of 8 bit and here we are storing 1st element of keyTemp into temp
    for(int i = 0 ; i < 3 ; i++){
        keyTemp[i] = keyTemp[i+1]; // shifting element of ketTemp array to left
    }
    keyTemp[3] = temp; // storing temp at last index of keyTemp
}

// SUBWORD function for key scheduling 
void subWord(unsigned char keyTemp[4]){
    for(int i = 0 ; i<4 ; i++){ // here i will apply subbyte to all element of keyTemp one by one 1st
        int t1,t2;
        t1 = keyTemp[i] & 15; // by doing and operation of keyTemp[i] with 15 we will get column to check in sub matrix
        t2 = keyTemp[i] >> 4; // by doing 4 times right shift operation on keyTemp[i] will get row to check in sub matrix
        keyTemp[i] = sub[t2][t1]; //we are cheking subbyte for element from sub table and update it in keyTemp[i].
    }
}

// let's define function to create all 44 words which will generate 11 round keys
void createWords(unsigned char key[4][4]){ // function will take key matrix and generate words.
    // first generate words[0] , words[1] , words[2] , words[3] from given key matrix
    for(int i = 0 ; i<4 ; i++){ 
        for(int j = 0 ; j<4 ; j++){
                words[i][j] = key[j][i]; // for ex. word[0] = {0x.. , 0x.. , 0x.. , 0x..} in form
        }
    }

    // generate words[4] to words[43] using fort loop i -> 4 to 43
    for(int i = 4 ; i<44 ; i++){
        unsigned char keyTemp[4]; // create temporary array of 4 element each of 8 bit whick we can pass to ROTWORD and SUBWORD function
        for(int j = 0 ; j<4 ; j++){
            keyTemp[j] = words[i-1][j]; // copy words[i-1] to keyTemp
        }
            if(i%4 == 0){ // if i is multiple of 4 then we need to apply ROTWORD and SUBWORD function and then XOR with Rcon[i/4]
                rotWord(keyTemp); // apply ROTWORD function and it will update keyTemp
                subWord(keyTemp); // apply SUBWORD function and it will update keyTemp
                for(int j = 0 ; j <4 ; j++){   // XOR with Rcon[i/4]
                    keyTemp[j] = keyTemp[j] ^ Rcon[(i/4)-1][j]; // here we are doing XOR with Rcon[(i/4)-1] because i start from 4 and Rcon start from 0
                }
            }

            for(int j = 0 ; j < 4 ; j++){// XOR with words[i-4]
                words[i][j] = words[i-4][j] ^ keyTemp[j];// here we are doing XOR with words[i-4] because i start from 4 and words start from 0
            }
    }
}

// let's define subbyte function which will take 1 byte and return 1 byte
unsigned char Subbytes(unsigned char a){ 
    unsigned char temp = a << 1; // left shift 1 time means multiply by 2
    if(a >> 7 == 1){ // if 1st bit of a is 1 then we need to XOR with 27 means polynomial (x^4 + x^3 + x + 1)
       temp = (temp ^ 27) ^ 1; // XOR with 27 and then XOR with 1
    }
    else{ // if 1st bit of a is 0 then we don't need to XOR with 27 beacause x^8 will not be there in polynomial temp.
        temp = temp ^ 1; // XOR with 1
    }
    int t1,t2; // t1 and t2 will store row and column of sub matrix
    t1 = temp & 0xf; // by doing and operation of temp with 15 we will get column to check in sub matrix
    t2 = temp >> 0x4; // by doing 4 times right shift operation on temp will get row to check in sub matrix
    return sub[t2][t1]; //we are cheking subbyte for element from sub table and return it.
}

// let's define function to apply shiftrow operation on matrix
void Shiftrow(unsigned char plaintext[4][4]){ 
    // 0th row will not change so we will not do anything for 0th row
    
    //1st row
    unsigned char t1 = plaintext[1][0]; // store 1st element of 1st row in t1
    for(int i = 0 ; i < 3 ; i++){
        plaintext[1][i] = plaintext[1][i+1]; // shift element of 1st row to left by 1
    }
    plaintext[1][3] = t1; // store t1 in last element of 1st row

    //2nd row
    unsigned char t2 = plaintext[2][0]; // store 1st element of 2nd row in t2
    unsigned char t3 = plaintext[2][1];
    plaintext[2][0] = plaintext[2][2]; // shift element of 2nd row to left by 2
    plaintext[2][1] = plaintext[2][3]; // shift element of 2nd row to left by 2
    plaintext[2][2] = t2; // store t2 in 3rd element of 2nd row
    plaintext[2][3] = t3;  // store t3 in 4th element of 2nd row
    
    //3rd row
    unsigned char t4 = plaintext[3][3]; // store last element of 3rd row in t4

   for(int i = 3 ; i>=1 ; i--){ 
        plaintext[3][i] = plaintext[3][i-1]; // shift element of 3rd row to right by 1
    }
    plaintext[3][0] = t4;   // store t4 in 1st element of 3rd row

    return;
}


// function to multiply given polynomial with x^2
unsigned char x2s(unsigned char s){ 
    unsigned char t;
    t = (s<<2); // left shift 2 times means multiply by 4
    if (s>>7 == 1) // if msb of s is 1 then we need to XOR with 54 (x(x^4 + x^3 + x + 1)) to remove x^9 term
    {
        t = t^54;
        if(s>>6 == 3){ // if 2nd msb of s is 1 then we need to XOR with 27 (x^4 + x^3 + x + 1) to remove x^8 term
        t = t^27;
    }
    }else if(s >> 6 == 1){ // if 2nd msb of s is 1 but 1st msb is 0 then we need to XOR with 27 
        t = t^27;
    }
    return t;
}


// funtion for mixcolumn operation
void mixColumn(unsigned char plaintext[4][4]){

    unsigned char temp[4]; // temp array to store column of matrix
    for (int c = 0; c < 4; c++) {
        // Extract the column from the given matrix and put it in temp
        for (int r = 0; r < 4; r++) {
            temp[r] = plaintext[r][c];
        }
        // Perform the MixColumns transformation on the column
        plaintext[0][c] = temp[0] ^ x2s(temp[1]) ^ x2s(temp[2]) ^ x2s(temp[3]) ^ temp[3]; // (x^2 + 1)S = x^2S ^ S
        plaintext[1][c] = x2s(temp[0]) ^ temp[0] ^ temp[1] ^ x2s(temp[2]) ^ x2s(temp[3]); // updating 2nd element of column
        plaintext[2][c] = x2s(temp[0]) ^ x2s(temp[1]) ^ temp[1] ^ temp[2] ^ x2s(temp[3]); // updating 3rd element of column
        plaintext[3][c] = x2s(temp[0]) ^ x2s(temp[1]) ^ x2s(temp[2]) ^ temp[2] ^ temp[3]; // updating 4th element of column
    } 
    return;
}

// let's define invSubbyte function which we will use in decryption
unsigned char invSubbytes(unsigned char a){// here we will take 1 byte and return 1 byte
    int row;  
    int col;
    for(int i = 0 ; i<16 ; i++){ // here we will find row and column of sub matrix for given byte by traversing 256 element 
        for(int j = 0 ; j< 16 ; j++){
            if(sub[i][j] == a){ // if we find element in sub matrix then we will store row and column in row and col variable
               row = i;
               col = j;
            }
        }
    }

    unsigned char t = (row << 4) | col; // here we will store row and column in temp of 8 bit
    if((t & 0x01) == 0){ // if lsb of t is 0 then we need to XOR with 27 means polynomial (x^4 + x^3 + x + 1)
        t = ((t ^ 1) ^ 27) >> 1; // XOR with 27 and then XOR with 1 and then right shift 1 time means divide by 2
        t = t | 0x80; // here we are setting 1st bit of t to 1 
    }
    else{  // if lsb of t is 1 then we don't need to XOR with 27.
        t = (t ^ 1) >> 1;
    }
    return t; 
}

// let's define function to apply inverse shiftrow operation on matrix
void invShiftrow(unsigned char plaintext[4][4]){
    // 0th row will not change so we will not do anything for 0th row

    //1st row
    unsigned char t1 = plaintext[1][3]; 
    for(int i = 3 ; i > 0 ; i--){
        plaintext[1][i] = plaintext[1][i-1]; // shift element of 1st row to right by 1
    }
    plaintext[1][0] = t1;     // store t1 in 1st element of 1st row

    //2nd row
    unsigned char t2 = plaintext[2][3];
    unsigned char t3 = plaintext[2][2];
    plaintext[2][3] = plaintext[2][1]; // shift element of 2nd row to right by 2
    plaintext[2][2] = plaintext[2][0]; // shift element of 2nd row to right by 2
    plaintext[2][1] = t2; // store t2 in 2nd element of 2nd row
    plaintext[2][0] = t3; // store t3 in 1st element of 2nd row
    
    //3rd row
    unsigned char t4 = plaintext[3][0]; // store 1st element of 3rd row in t4

   for(int i = 0 ; i<3 ; i++){
        plaintext[3][i] = plaintext[3][i+1]; // shift element of 3rd row to left by 1
    }
    plaintext[3][3] = t4; // store t4 in last element of 3rd row

    return;
}

unsigned char mat_polynomial(unsigned char a, unsigned char b)
{
    unsigned char res = 0;
    unsigned char i;
    unsigned char temp;
    for (i = 0; i < 8; i++)
    {
        if ((b & 1) == 1)
            res ^= a;
        temp = (a & 0x80);
        a <<= 1;
        if (temp == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return res;
}


// function for inverse mixcolumn operation
void invMixColumn(unsigned char plaintext[4][4]){

    unsigned char temp[4];
    for (int c = 0; c < 4; c++) {
        // Extract the column from the state matrix and put it in temp
        for (int r = 0; r < 4; r++) {
            temp[r] = plaintext[r][c];
        }
        // Perform the MixColumns transformation on the column
        plaintext[0][c] = mat_polynomial(temp[0] , 165) ^ mat_polynomial(temp[1] , 7) ^ mat_polynomial(temp[2] , 26) ^ mat_polynomial(temp[3] , 115); // updating 1st element of column
        plaintext[1][c] = mat_polynomial(temp[0] , 115) ^ mat_polynomial(temp[1] , 165) ^ mat_polynomial(temp[2] , 7) ^ mat_polynomial(temp[3] , 26); // updating 2nd element of column
        plaintext[2][c] = mat_polynomial(temp[0] , 26) ^ mat_polynomial(temp[1] , 115) ^ mat_polynomial(temp[2] , 165) ^ mat_polynomial(temp[3] , 7); // updating 3rd element of column
        plaintext[3][c] = mat_polynomial(temp[0] , 7) ^ mat_polynomial(temp[1] , 26) ^ mat_polynomial(temp[2] , 115) ^ mat_polynomial(temp[3] , 165); // updating 4th element of column
    } 
    return;
}

// encryption function to encrypt plaintext
void Encryption(unsigned char plaintext[4][4]){
    // there are 9 same rounds in AES encryption algorithm which is XOR -> Subbytes -> Shiftrow -> Mixcolumn 
    for(int i = 0 ; i<9 ; i++){ // 9 rounds
        for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = plaintext[k][j] ^ words[i*4 + j][k]; // XOR operation
            }
        }
        
        // Subbytes operation
        for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = Subbytes(plaintext[k][j]); 
            }
        }

        Shiftrow(plaintext); // Shiftrow operation
        mixColumn(plaintext); // Mixcolumn operation
    }

    // after 9 rounds we have to do XOR -> Subbytes -> Shiftrow -> XOR
    for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = plaintext[k][j] ^ words[9*4 + j][k];
            }
    }
    
    // Subbytes operation
    for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = Subbytes(plaintext[k][j]);
            }
    }

    // Shiftrow operation
    Shiftrow(plaintext);

    // XOR operation
    for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = plaintext[k][j] ^ words[10*4 + j][k];
            }
    } 

}

// decryption function to decrypt ciphertext
void Decryption(unsigned char plaintext[4][4]){
    // we have to do reverse of encryption algorithm
    // XOR -> InvShiftrow -> InvSubbytes -> XOR
    for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = plaintext[k][j] ^ words[10*4 + j][k]; //k10 will be use (key10 will generate from words[40] to words[43]])
            }
    } 
    invShiftrow(plaintext);
    for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = invSubbytes(plaintext[k][j]);
            }
    }
    
    // XOR operation
    for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = plaintext[k][j] ^ words[9*4 + j][k]; // key9 will use (key9 will generate from words[36] to words[39])
            }
    }
    
    // there are 9 same rounds in AES decryption algorithm which is InvMixcolumn -> InvShiftrow -> InvSubbytes -> XOR
    for(int i = 8 ; i>=0 ; i--){
        invMixColumn(plaintext);
        invShiftrow(plaintext);
        for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = invSubbytes(plaintext[k][j]);
            }
        }
        // XOR operation
        for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                plaintext[k][j] = plaintext[k][j] ^ words[i*4 + j][k];
            }
        }        
    } 
    
}

int main(){
    // we have to take plain text input from user in hexa decimal of 128 bit and key of 128 bit and store it in 2D array of 4X4
    unsigned char plaintext[4][4], key[4][4];

    printf("Enter PlainText in 16 HexaDecimal: ");
    for(int i = 0 ; i<4 ; i++){
        for(int j = 0 ; j<4 ; j++){
            unsigned char temp;
            scanf("%hhx" , &temp); // taking input in hexa decimal
            plaintext[j][i] = temp; // storing it in 2D array
        }
    }

    printf("Enter key in 16 HexaDecimal: ");
    for(int i = 0 ; i<4 ; i++){
        for(int j = 0 ; j<4 ; j++){
            unsigned char temp;
            scanf("%hhx" , &temp); // taking input in hexa decimal
            key[j][i] = temp; // storing it in 2D array
        }
    }

    createWords(key); // creating 44 words from key and storing it in words array
    Encryption(plaintext); // encrypting plaintext

    printf("\n");
    printf("ciphertext is: --------------------------------------------------------------------------------\n\n");
    //printing ciphertext
    for(int i = 0 ; i< 4 ; i++){
        for(int j = 0 ; j<4 ; j++){
            printf("%hhx " , plaintext[j][i]); // out cipher text is stored in plaintext array
        }
    }
    
    printf("\n\n");


    Decryption(plaintext); // decrypting ciphertext
    printf("decrypted text is: --------------------------------------------------------------------------------\n\n");
    //printing decrypted text
    for(int i = 0 ; i< 4 ; i++){
        for(int j = 0 ; j<4 ; j++){
            printf("%hhx " , plaintext[j][i]); // out decrypted text is stored in plaintext array
        }
    }

    printf("\n");

    
    return 0;
}

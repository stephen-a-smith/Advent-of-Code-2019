#include <stdio.h>
#include <stdlib.h>
long long * readFile(char argv[], int *len);
int runProgram(long long * program, long long **ip_in, int len, int input, int* base);
void add(long long in1, long long in2, long long * out);
void mul(long long in1, long long in2, long long * out);
void IN(long long* address, int input);
void output(long long address);
void JNZ(long long* program, long long** ip, long long op1, long long op2);
void JZ(long long* program, long long **ip, long long op1, long long op2);
void LT(long long op1, long long op2, long long * out);
void EQ(long long op1, long long op2, long long* out);


enum dir{up, right, down, left};
int main(int argc, char *argv[]){
    int len;
    long long *arr = readFile(argv[1], &len);
    
    //alloc a large section of extra memory
    arr = realloc(arr, len*len*len*sizeof(*arr));
    int i, j;
    for(i = len; i < len*len; i++){
        arr[i] = 0;
    }
    int bounds = 100;
    len *= len;
    long long *ip_in = arr;
    int base = 0;
    int input = 1;
    enum dir currentDir = up;
    int hull[bounds][bounds];
    for(i = 0; i < bounds; i++){
        for(j = 0; j < bounds; j++){
            hull[i][j] = 0;
        }
    }

    int currentY = bounds/2;
    int currentX = bounds/2;
    int output;
    while(*ip_in != 99){
        
        output = runProgram(arr, &ip_in, len, input, &base);
        if(output == -1){break;}
        hull[currentY][currentX] = output;
        

        output = runProgram(arr, &ip_in, len, input, &base);

        if(output == 0){
            switch(currentDir){
                case up:
                    currentDir = left;
                    break;
                case right:
                    currentDir = up;
                    break;
                case down:
                    currentDir = right;
                    break;
                case left:
                    currentDir = down;
                    break;
            }    
        } else {
            switch(currentDir){
                case up:
                    currentDir = right;
                    break;
                case right:
                    currentDir = down;
                    break;
                case down:
                    currentDir = left;
                    break;
                case left:
                    currentDir = up;
                    break;
            }
        }


        switch(currentDir){
            case up:
                currentY--;
                break;
            case right:
                currentX++;
                break;
            case down:
                currentY++;
                break;
            case left:
                currentX--;
                break;
        }
        input = hull[currentY][currentX];
    }

    for(i = 0; i < bounds; i++){
        for(j = 0; j < bounds; j++){
            //for readability
            if(hull[i][j] == 0){
                printf(".");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }
}

int runProgram(long long* program, long long **ip_in,  int len, int input, int* base_in){
    long long *ip = *ip_in;
    int base = *base_in;
    int i;
    for(;;){
        int opcode = (*ip)%100;
        if(opcode == 99){
            *ip_in = ip;
            return -1;
        }    
    
        short op1_mode = ((*ip)/100) % 10;
        short op2_mode = ((*ip)/1000) % 10;
        short op3_mode = (*ip)/10000;
        long long  op1, op2;
        long long* op3;
        if(op1_mode == 1){
            op1 = *(ip+1);
        } else if (op1_mode == 0) {
            op1 = *(program + *(ip+1));
        } else {
            op1 = *(program + base + *(ip+1));
        }
        if(op2_mode == 1){
            op2 = *(ip+2);
        } else if (op2_mode == 0){
            op2 = *(program + *(ip+2));
        } else{
            op2 = *(program + base + *(ip+2));
        }
        if(op3_mode == 0){
            op3 = program + *(ip+3);        
        } else {
            op3 = program + base + *(ip+3);
        }

        switch(opcode){
            case 1: // ADD
                add(op1, op2, op3);
                ip += 4;
                break;
            case 2: // MUL
                mul(op1, op2, op3);
                ip += 4;
                break;
            case 3: // IN
                if(op1_mode == 0){
                    IN(program + *(ip+1), input);
                } else {
                    IN(program + base + *(ip+1), input);
                } 
                ip += 2;
                break;
            case 4: //OUT
                //output(op1);
                ip += 2;
                *ip_in = ip;
                *base_in = base;
                return op1;
                break;
            case 5: //JNZ
                JNZ(program, &ip, op1, op2);
                break;
            case 6: //JZ
                JZ(program, &ip, op1, op2);
                break;
            case 7: //LT
                LT(op1, op2, op3);
                ip += 4;
                break;
            case 8://EQ
                EQ(op1, op2, op3);
                ip += 4;
                break;
            case 9: //adjust base;
                base += op1;
                ip += 2;
                break;
        }   
    }
}

void JNZ(long long* program, long long** ip, long long op1, long long op2){
    if(op1 != 0){
        *ip = program+op2;
    } else {
        *ip += 3;
    }
}

void JZ(long long* program, long long** ip, long long op1, long long op2){
    if(op1 == 0){
        *ip = program+op2;
    } else {
        *ip += 3;
    }
}

void LT(long long op1, long long op2, long long* op3){
    if(op1 < op2){
        *op3 = 1;
    } else {
        *op3 = 0;
    }
}

void EQ(long long op1, long long op2, long long* op3){
    if(op1 == op2){
        *op3 = 1;
    } else {
        *op3 = 0;
    }
}
void output(long long address){
    printf("%lld\n", address);
}

void IN(long long* address, int input){
    *address = input;
}

void add(long long in1, long long in2, long long* out){
    *out = in1 + in2;
}

void mul(long long in1, long long in2, long long* out){
    *out = in1 * in2;
}

long long* readFile(char *argv, int *len){
    FILE *fp;
    fp = fopen(argv, "r");
    
    long long* ptr = (long long*) malloc(sizeof(long long));
    int index = 0;
    
    /*
        fscanf() returns the number of elements scanned, then moves the file pointer
        we only want to break the loop when it stops reciving valid input, or, when it
        returns any number other than 1

        By using "%d," instead of "%d" we automatically strip the delimiting commas  
    */
    while(fscanf(fp, "%lld,", ptr+index) == 1){
        index++;
        ptr = (long long*) realloc(ptr, (index+1)*sizeof(long long));
    }
    fclose(fp);
    
    *len = index;
    return ptr;
}

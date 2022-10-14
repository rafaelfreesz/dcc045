//
// Created by Rafael on 10/11/2022.
//

#include "LexicalAnalyzer.h"
#include <ctype.h>

void buildLexicalAnalyzer(char* fileName, int isThereArgumentForFile){

    if(isThereArgumentForFile){
        
        char *dot  = strrchr(fileName, '.');
        char *extension = NULL;

        if (!dot) { //If file doesnt have extension
            extension = ".cmm";

        } else {
            
            //If file has only dot as extension
            if((strcmp(".", dot) == 0)) {

                extension = "cmm";

            }else{ //Other files are not supported

                if((strcmp(dot, ".cmm") != 0)) sendSystemError(FILENOTSUPPORTED);
            }
            

        }

        if(extension){ //If extension was added concat it to the fileName to make it able for reading

            strcat(fileName, extension);
        }
        
        //Check if the file was open successfully
        if((analyser.sourceFile= fopen(fileName,"r"))==NULL){
            sendSystemError(FILENOTFOUND);
        }

        // analyser.bufferRef.referedBuffer=MAINBUFFER;
        // analyser.bufferRef.bufferIndex=0;

        //Read block from the file
        analyser.blockLength = fread(analyser.mainBuffer, 1, BUFFERSIZE, analyser.sourceFile);
        printf("\nBloco: %d\n", analyser.blockLength);        
        analyser.positionInMainBuffer = 0;
        analyser.positionInLexemeBuffer = 0;


        //Treatment
        // int tam = length;
        // char c = analyser.mainBuffer[0];
        // int pos = 0;
        // while(pos < tam){
        //     printf("%c", analyser.mainBuffer[pos]);
        //     pos++;
        // }

    }
    
    // else{

    //     char *inputBuffer;
    //     size_t bufsize = BUFFERSIZE;
    //     size_t characters;

    //     inputBuffer = (char *)malloc(bufsize * sizeof(char));
    //     if( inputBuffer == NULL)
    //     {
    //         perror("Unable to allocate buffer");
    //         exit(1);
    //     }
        
    //     printf("Entered input mode from keyboard: ");
    //     characters = getline(&inputBuffer,&bufsize,stdin);
    //     inputBuffer[characters + 1] = '\0';
    //     // printf("%zu characters were read.\n",characters);
    //     // printf("You typed: '%s'\n",buffer);

    //     // Read block from the keyboard
    //     int posInputBuffer = 0;
    //     int posMainBuffer = 0;

    //     while(posMainBuffer < BUFFERSIZE){
            
    //         posMainBuffer = 0;
    //         if(inputBuffer[posInputBuffer] == '\0') break;

    //         // printf("Main buffer: %d\n", posMainBuffer);
    //         // printf("Input buffer: %d\n", posInputBuffer);

    //         analyser.mainBuffer[posMainBuffer] = inputBuffer[posInputBuffer];
    //         printf("%c", analyser.mainBuffer[posMainBuffer]);
    //         posMainBuffer++;
    //         posInputBuffer++;

    //     }   
        
    //     free(inputBuffer);


    // }
    
}


int nextToken(){
    // Token token;
    // short foundToken=0;S
    char *lexem = (char *)malloc(100 * sizeof(char));
    char character = analyser.mainBuffer[analyser.positionInMainBuffer];
    lexem[analyser.positionInLexemeBuffer] = character;
    analyser.positionInLexemeBuffer++;

    short done = 0;
    short currentState = 0; 


    while(!done){
        
        printf("%d\n", analyser.positionInMainBuffer);
        // printf("%d\n", analyser.blockLength);


        if(analyser.positionInMainBuffer == BUFFERSIZE-1 && character != EOF){
            printf("Read new block\n");
            analyser.positionInMainBuffer = 0;
            analyser.blockLength = fread(analyser.mainBuffer, 1, BUFFERSIZE, analyser.sourceFile);
        }

        switch(currentState){

            case 0:

                if(isdigit(character)){
                    currentState = 45;
                    character = analyser.mainBuffer[analyser.positionInMainBuffer++];

                }else{
                    // printf("EOF\n");
                    // if(character == EOF) done = 1;
                    done = 1;
                }

                break;

            case 45:
                
                if(isdigit(character)) {
                    // printf("ESTADO 45\n");
                    lexem[analyser.positionInLexemeBuffer] = analyser.mainBuffer[analyser.positionInMainBuffer];
                    analyser.positionInLexemeBuffer++;
                    character = analyser.mainBuffer[analyser.positionInMainBuffer++];
                }else{
                    if (character == '.'){
                        currentState = 51;
                        lexem[analyser.positionInLexemeBuffer] = analyser.mainBuffer[analyser.positionInMainBuffer];
                        analyser.positionInLexemeBuffer++;
                        character = analyser.mainBuffer[analyser.positionInMainBuffer++];
                    }else{
                        
                        printf("Lexema: %s\n", lexem);
                        return NUMINT;
                    }
                }
                
                break;
            
            case 51:
                
                if(isdigit(character)) {
                    // printf("ESTADO 51\n");
                    currentState = 52;
                    lexem[analyser.positionInLexemeBuffer] = analyser.mainBuffer[analyser.positionInMainBuffer];
                    analyser.positionInLexemeBuffer++;
                    character = analyser.mainBuffer[analyser.positionInMainBuffer++];
                }else{

                    return POINT;

                }

                break;

            case 52:

                if(isdigit(character)){
                    // printf("ESTADO 52\n");
                    lexem[analyser.positionInLexemeBuffer] = analyser.mainBuffer[analyser.positionInMainBuffer];
                    analyser.positionInLexemeBuffer++;
                    character = analyser.mainBuffer[analyser.positionInMainBuffer++];

                }else{
                    // printf("ESTADO 53\n");
                    currentState = 53;
                    done = 1;
                    printf("Lexema: %s\n", lexem);
                    return NUMFLOAT;
                }
                
                break;

        }
    }

    return -1;
    free(lexem);
}
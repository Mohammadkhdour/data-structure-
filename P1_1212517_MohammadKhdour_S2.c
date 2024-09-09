
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    struct node* next;
    struct node* prev;
}node;
FILE *read_file,*print_file;
void Menu();
void selectOperation(node* list[],node* print[]);
int countNode(struct node* list);
void reverseList(node* list);
void Reader( node* list[]);
void printAllNumbersList( node* list[]);
void printList (node* list);
void printInFile(node* list[],int size);
node* makeEmpty( node* list);
void insertion( node* list,int element);
void insertionAtFirst( node* A,int element);
int isEmpty( node* list);
int countNumbersFile(FILE *A);
void readNegativeNumber(node* list);
node* addition (node* list[],int count);
node* additionTwoNumber(node* list1,node* list2);
node* subTwoNumber(node* A1,node* A2);
void correctNumber(node* list1);
node* copyList(node* list) ;
int checkNegativeNumber(node* list);
node* SignConvert(node* list);
void addZeroes(node *list1,node *list2);
int compereList(node* list1,node* list2);
node* Multiplication(node* list1, node* list2);
node* deleteLists(node* list[]);
node* Division(node* list1,node* list2);

int main() {
    int x= countNumbersFile(read_file);
    node *header[x];
    node *printFile[5];
    for(int i=0;i<x;i++)
    {
        header[i] = makeEmpty(header[i]);
    }
    for(int i=0;i<5;i++)
    {
        printFile[i] = makeEmpty(printFile[i]);
    }
    printf("count of numbers in file is=%d\n",x);
    selectOperation(header,printFile);
    return 0;
}
void Menu(){
    printf("select operation\n");
    printf("1_read input file\n");
    printf("2_Add Numbers\n");
    printf("3_subtraction Numbers\n");
    printf("4_Multiply Numbers\n");
    printf("5_Divide Numbers\n");
    printf("6_Print the results in file\n");
    printf("7_Exit");
}
void selectOperation(node* list[],node* print[]){
    int select;//to select operation I want from user;
    int x;//to select index from user
    int y;//to select index from user
    int count=0;//this integer count the number of time that we made operation
    do {
        Menu();
        scanf("%d", &select);

        switch (select) {
            case 1:
                Reader(list);
                printAllNumbersList(list);
                deleteLists(list);
                break;
            case 2:
                Reader(list);
                printf("select two number to add them\n");
                scanf("%d", &x);
                scanf("%d", &y);
                printList((print[count] = additionTwoNumber(list[x-1],list[y-1])));//choose the index of list in file to add them and print it
                count++;
                deleteLists(list);
                break;
            case 3:
                Reader(list);
                printf("select two number to subtract them\n");
                scanf("%d", &x);
                scanf("%d", &y);
                printList((print[count] = subTwoNumber(list[x-1],list[y-1])));//choose the index of list to sub them and print it
                count++;
                deleteLists(list);
                break;
            case 4:
                Reader(list);
                printf("select two number to multiply them\n");
                scanf("%d", &x);
                scanf("%d", &y);
                printList((print[count] = Multiplication(list[x-1], list[y-1])));
                count++;
                deleteLists(list);
                break;
            case 5:
                Reader(list);
                printf("select two number to divide them\n");
                scanf("%d", &x);
                scanf("%d", &y);
                printList((print[count] = Division(list[x-1],list[y-1])));
                count++;
                deleteLists(list);
                break;
            case 6:
                printInFile(print,count);
                printf("The results add to file successfully\n");
                break;
            case 7:
                printf("The system will close. Thank you");
                exit(0);
                break;
            default:
                printf("the operation doesn't found!!\n\n");
        }
    }while(select);
}

void Reader( node * list[]){
    read_file= fopen("Input.txt","r");
    if(read_file==NULL){
        printf("the file is empty!!");
        exit(-1);

    }
    else{
        char c;//to read digit by digit
        int count=0;// for array index
        int digit;// this is in element saved as linked list

        while ((c= fgetc(read_file))!= EOF){//wile-loop to read file from the beginning to end
            if(c=='-'){
                readNegativeNumber(list[count]);
                count++;
                continue;
            }
            else if(c>='0'&& c<='9')//to check if c is a number or not
            {
                digit = c - '0';//to convert the char to integer
                insertion(list[count],digit);//here this function to insert a digit to linked list in index count
            }
            else if(c =='\n')// to check if c reached to new line
                count++;// if c reached new line we will add to count one to make new list
            else
                continue;
        }
    }
    fclose(read_file);//close file

}
void printInFile(node* list[],int size) {//print the result in file
    print_file = fopen("Output.txt", "w");//open the file to write in
    if (print_file == NULL) {//check if the file is NULL
        printf("Error: could not open file\n");//massage error
        return;
    }
    for (int i = 0; i < size; ++i) {//loop to print the parameter list which contains the results
        node *current = copyList(list[i]);
        if(current->next!=NULL&&current->next->num==11){//check if the number is negative
            fprintf(print_file,"%c",'-');
            current=current->next;
        }
        while (current->next != NULL) {
            fprintf(print_file, "%d ", current->next->num);
            current = current->next;
        }
        fprintf(print_file,"\n");
    }

    fclose(print_file);

}
node* deleteLists(node* list[]){
    struct node* temp;
    struct node* p;
    for (int i = 0; i < countNumbersFile(read_file); ++i) {
        p = list[i]->next;
        list[i]->next = NULL;
        list[i]->prev=NULL;

        while (p != NULL) {
            temp = p->next;
            free(p);
            p = temp;
        }
    }
    return p;
}

void printAllNumbersList( node* list[]){
    for(int i=0;i< countNumbersFile(read_file);i++) {
        if (list[i]->next == NULL)
            printf("the list is empty");
        else {
            while (list[i]->next != NULL) {
                printf("%d ", list[i]->next->num);
                list[i] = list[i]->next;
            }
            printf("\n");
        }
        while (list[i]->prev != NULL) {
            list[i] = list[i]->prev;
        }
    }
}
void printList(node* list){
    if (isEmpty(list))
        printf("the list is empty");
    else {
        if(list->next->num==11){//check if the number is negative
            printf("%c",'-');
            list=list->next;
        }
        while (list->next != NULL) {// print digit digit to the user
            printf("%d", list->next->num);
            list = list->next;
        }

    }
    printf("\n");
}
int isEmpty( node* list){//check if the list is empty or not
    if(list==NULL)
        return 1;
    return list->next==NULL&&list->prev==NULL;
}
node* makeEmpty( node* list){// this function is important to each new list to make it empty to used it

    list= ( node*)malloc(sizeof( node));// creat new node and make list equal it
    if(list==NULL)//check if list is NULL
        printf("out of memory");
    list->next=NULL;//make next state equal to NULL
    list->prev=NULL;//make prev state equal to NULL
    return list;//return new list empty
}
void insertion( node* list,int element){//insert at end of linked list

    struct node* newNode,*temp;
    newNode=(node*) malloc(sizeof(node));//creat new node
    temp=list;

    newNode->num = element;
    newNode->next = NULL;
    while (temp->next != NULL) {//while-loop while be false when temp reached to final index
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}
void insertionAtFirst( node* A,int element){
    struct node* newNode;
    newNode=(struct node*) malloc(sizeof(struct node));
    newNode->num=element;
    newNode->prev=A;
    newNode->next=A->next;
    A->next=newNode;
}
int countNumbersFile(FILE *A){
    A= fopen("Input.txt","r");
    if (A==NULL){
        printf("there is Error!!!");
        exit(-1);
    }
    int count= 0;
    int x;
    while(fscanf(A,"%d",&x)!=EOF){
        count++;
    }
    fclose(A);
    return count;
}

void readNegativeNumber(node* list){
    char c;
    int digit;
    while((c= fgetc(read_file)) !='\n')
        if(c>='0'&& c<='9')//to check if c is a number or not
        {
            digit = -(c - '0');//to convert the char to integer
            insertion(list,digit);//here this function to insert a digit to linked list in index count
        }

}

void reverseList(node* list) {
    node* current  = list->next;
    node* prev = NULL;
    node* nxt  = current->next;
    while(current!=NULL){
        current->next = prev;
        current->prev = nxt;
        prev = current;
        current = nxt;

        if(nxt!=NULL)
            nxt = nxt->next;
    }

    list->next = prev;
    prev->prev = list;
}

int countNode(node* list){//count number of digit in the list
    int count=0;
    node* cop= copyList(list);
    while(cop->next!=NULL){
        count++;
        cop=cop->next;
    }
    return count;
}
void correctNumber(node* list1){//we use this function to deal with zero in sub operation
    node* temp=list1;
    do {
        list1->next->num += 9;//replace zero to 9
        list1 = list1->next;
    } while (list1 != NULL && list1->next->num == 0);
    list1->next->num -= 1;//when we find number greater than zero sub one from it
    list1=temp;
    list1->num += 10;
}
node* copyList(node* list) {//copy list to unchanged the original list
    node* newList = NULL;
    newList=makeEmpty(newList);
    node* temp = list->next;
    while (temp != NULL) {
        insertion(newList, temp->num);
        temp = temp->next;
    }
    return newList;
}
int checkNegativeNumber(node* list){//check if number is negative or not
    int negative=0;
    node *cop= copyList(list);
    while(cop->next!=NULL){
        if(cop->next->num>0) {
            negative = 0;
            break;
        }
        else if(cop->next->num<0){
            negative=1;
            break;
        }
        cop=cop->next;
    }
    return negative;
}
node* SignConvert(node* list){
    node* new;
    new= makeEmpty(new);
    node* cop= copyList(list);
    int x;
    while(cop->next!=NULL){
        x=cop->next->num;
        x*=-1;
        insertion(new,x);
        cop=cop->next;
    }
    return new;
}
void addZeroes(node *list1,node *list2){//add zero to number which have fewer numbers of digit to make them equal in digit
    int num1= countNode(list1);
    int num2= countNode(list2);
    while(num2> num1){
        insertionAtFirst(list1,0);
        num1++;
    }
    while(num2<num1){
        insertionAtFirst(list2,0);
        num2++;
    }
}
int compereList(node* list1,node* list2){//compare between to numbers
    addZeroes(list1,list2);
    node* list11= copyList(list1);
    node*list22= copyList(list2);
    while(list11->next!=NULL&&list22->next!=NULL)
    {
        if(list11->next->num > list22->next->num){
            return 1;
        }
        else if(list11->next->num < list22->next->num){
            return -1;
        }
        else{
            list11=list11->next;
            list22=list22->next;
        }

    }
    return 0;
}node* subTwoNumber(node* A1,node* A2) {//this function is true when num1>num2
    node* list1;
        list1= makeEmpty(list1);
    node* list2;
    list2= makeEmpty(list2);
    node* subList;
    subList= makeEmpty(subList);
    if(compereList(A1,A2)==-1) {//compare if number 1 less than number 2 the result will be negative
        if (checkNegativeNumber(A2) == 1) {//if number 2 is negative than number 1 will be negative, so we must convert sign
            list1= copyList(SignConvert(A1));
            list2= copyList(SignConvert(A2));
        }  else if(checkNegativeNumber(A2) == 0 && checkNegativeNumber(A1) == 0){
            list1 = copyList(A2);
            list2 = copyList(A1);
        }
        else if(checkNegativeNumber(A2) == 0 && checkNegativeNumber(A1) == 1){//here negative sub negative be positive so the result will be addition two number
            subList= additionTwoNumber(SignConvert(A1), A2);
            insertionAtFirst(subList,11);
            return subList;
        }
        else{
            list2 = copyList(SignConvert(A1));
            list1 = copyList(A2);
        }
    } else {
        if (checkNegativeNumber(A1) == 1) {
            list1= copyList(SignConvert(A2));
            list2= copyList(SignConvert(A1));
        }
        else if(checkNegativeNumber(A1)==0 && checkNegativeNumber(A2)==1){
            return additionTwoNumber(A1, SignConvert(A2));
        }
        else if(checkNegativeNumber(A1)==0&& checkNegativeNumber(A2)==0){
            list1 = copyList(A1);
            list2 = copyList(A2);
        }
    }
    int sub;
    int num1, num2;
    reverseList(list1);
    reverseList(list2);
    addZeroes(list1,list2);
    list1 = list1->next;
    list2 = list2->next;

    while (list1 != NULL) {
        num1 = list1->num;
        num2 = list2->num;
        sub = num1 - num2;
        if (sub >= 0 && sub <= 9) {
            insertionAtFirst(subList, sub);
        } else {//if sub two digit is negative
            if (list1->next!=NULL&&list1->next->num == 0) {//if next digit is zero we cant take one from it
                correctNumber(list1);
                sub = (list1->num) - num2;
                insertionAtFirst(subList, sub);
            } else {//if next digit is greater than 0
                num1 = num1 + 10;//add to number 10 to be subtraction between two number positive
                list1->next->num -= 1;
                sub = num1 - num2;
                insertionAtFirst(subList, sub);
            }
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    if(compereList(A1,A2)==-1 || checkNegativeNumber(A1)==1&& checkNegativeNumber(A2)==0)
        insertionAtFirst(subList,11);
    return subList;
}
node* additionTwoNumber(node* list11,node*list22) {
    node *list1= copyList(list11);
    node *list2= copyList(list22);
    node *addList;
    addList= makeEmpty(addList);
    if(checkNegativeNumber(list1)==1 || checkNegativeNumber(list2)==1) {//if one of list is negative
        if(checkNegativeNumber(list1)==0&& checkNegativeNumber(list2)==1){//if list 1 is positive and list 2 negative
            if(compereList(list11, SignConvert(list22))==-1) {//if result is negative add negative sign
                insertionAtFirst(addList, 11);
                addList= subTwoNumber(SignConvert(list2),list1);

            }
            else
                addList= subTwoNumber(list1, SignConvert(list2));
        }
        else if(checkNegativeNumber(list1)==1&& checkNegativeNumber(list2)==1){//if two list is negative than result is negative we must add negative sign
            addList= subTwoNumber(SignConvert(list1),list2);
            insertionAtFirst(addList,11);
        }
        else if(checkNegativeNumber(list1)==1&& checkNegativeNumber(list2)==0){//if list 1 negative and list 2 positive
            if(compereList(SignConvert(list11), list22)==1){//compere if negative greater than positive add negative sign
                addList= subTwoNumber(SignConvert(list1),list2 );
                insertionAtFirst(addList,11);
            }
            else
                addList= subTwoNumber(list2,SignConvert(list1) );
        }
        else
            addList= subTwoNumber(list1,list2);
    }
    else {//if to number is positive
        int x, carry = 0;
        int num1, num2;
        addZeroes(list1, list2);
        reverseList(list1);
        reverseList(list2);
        while (list1->next != NULL || carry == 1) {//list1 equal node list 2 so the while loop while be true until reach Null and carry be zero
            list1 = list1->next;
            list2 = list2->next;

            if (list1 == NULL && carry == 1) {//when two list be NULL and there are carry we add it to list
                insertionAtFirst(addList, carry);
                break;
            } else {
                num1 = list1->num;
                num2 = list2->num;
            }
            x = num1 + num2 + carry;
            if (x > 9) {
                x = x % 10;
                insertionAtFirst(addList, x);
                carry = 1;
            } else if (x >= 0) {
                insertionAtFirst(addList, x);
                carry = 0;
            }
        }
    }
    return addList;
}
node* Multiplication(node* list1, node* list2){
    node* multList;
    multList= makeEmpty(multList);
    node* add[countNode(list1)];//array list toke number of digit list1 size of array
    node* list11= copyList(list1);
    node* list22= copyList(list2);
    if(checkNegativeNumber(list11)==1)//if it negative convert to positive
        list11= SignConvert(list11);
    if(checkNegativeNumber(list22)==1)//if it negative convert to positive
        list22=SignConvert(list22);
    for (int i = 0; i < countNode(list1); ++i) {
        add[i]= makeEmpty(add[i]);
    }
    int mult=1,carry=0,count=0,index=0;
    reverseList(list11);
    reverseList(list22);
    for(int i;list11->next!=NULL;list11=list11->next){
        carry=0;
        i=list11->next->num;
        if(index>0){//when number of add list greater than 1 add zeroes
            for (int k = 0; k < index; ++k) {
                insertion(add[index],0);
            }
        }
        for (int j; list22->next!=NULL;list22=list22->next) {
            j=list22->next->num;
            mult=(i*j)+carry;
            if(mult>9){
                carry=mult/10;
                mult=mult%10;
            }
            else
                carry=0;
            insertionAtFirst(add[index],mult);
            count++;
        }
        while (count != 0) {//reverse list22 to point in first node
            list22 = list22->prev;
            count--;
        }
        if(carry>0){
            insertionAtFirst(add[index],carry);
        }
        index++;
    }
    multList= addition(add, countNode(list1));
    if(checkNegativeNumber(list1)==1^checkNegativeNumber(list2)==1)//check if one of them negative and add sign of negative
        insertionAtFirst(multList,11);

    return multList;
}
node* addition (node* list[],int count){//function add more than one number
    node* add;
    add=list[0];
    for (int i = 1; i < count; ++i) {
        add= additionTwoNumber(add,list[i]);
    }
    return add;
}

node* Division(node* list1,node* list2){
    node* newList;
    newList= makeEmpty(newList);
    node* divList;
    divList= makeEmpty(divList);
    if(checkNegativeNumber(list1)==1^checkNegativeNumber(list2)==1){//check if one of the list is negative than add negative sign
        insertionAtFirst(divList,11);//in print list 11 convert to negative sign
    }
    if(checkNegativeNumber(list1)==1)
        list1= SignConvert(list1);//convert to positive
    if(checkNegativeNumber(list2)==1)
        list2=SignConvert(list2);//convert to positive
    int count;//this is the result for every division operation
    while(list1->next!=NULL){
        count=0;
        list1=list1->next;
        insertion(newList,list1->num);//insert in new list number in the list1
        while(compereList(newList,list2)==-1&&list1->next!=NULL){//if newList is less than list2 insert on it until be more than it
            list1=list1->next;
            insertion(divList,0);//insert zero for divList for every insert in newList
            insertion(newList,list1->num);
        }
        node* sub=newList;
        while(compereList(sub,list2)>=0){//if sub which equal newList greater than divider subtraction from sub list amount list2
            sub= subTwoNumber(sub,list2);
            count++;
        }
        insertion(divList,count);
        newList=sub;// make newList equal remainder
    }
    return divList;
}
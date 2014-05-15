#include "BF_debug_interp.h"

BF_debug_interp::BF_debug_interp(QString s, int l, QTextBrowser *br) throw (const std::string)
{
    nextInstr =0;
    debugging = false;
    textBrowser =br;
    code = ExtractCodeFromString(s);
    if(!checkIfBuildable())
        throw (std::string)"blad";
	code_ptr = -1;
	mem_ptr =0;
    memory = new unsigned char[l];
    //val =0;
    for(int i =0; i < l; i++)
        memory[i]=0;
	len = l;
    connect(this, SIGNAL(sign(QString)), this, SLOT(slot1(QString)));
}

BF_debug_interp::BF_debug_interp(QString s, int l, QTextBrowser *br, QLabel *lab, QTabWidget * tw) throw (const std::string)
{
    nextInstr =0;
    debugging = false;
    textBrowser =br;
    label = lab;
    tabWidget = tw;
    code = ExtractCodeFromString(s);
    if(!checkIfBuildable())
        throw (std::string)"blad";
    code_ptr = -1;
    mem_ptr =0;
    memory = new unsigned char[l];
    for(int i =0; i < l; i++){
        memory[i]=0;
        //tabWidget->setTabText();
    }
    lab->setText("0");
    len = l;
    connect(this, SIGNAL(sign(QString)), this, SLOT(slot1(QString)));
    connect(this, SIGNAL(sigLabel()), this, SLOT(acLabel()));
    connect(this, SIGNAL(sigList(int)), this, SLOT(acList(int)));

}
QString BF_debug_interp::ExtractCodeFromString(QString s){
    QString code = "";
    for(int i =0; i < s.length(); i++)
            if(s[i] == QChar('+') || s[i] == QChar('-') || s[i] == QChar('>')
                    || s[i] == QChar('<') || s[i] == QChar(']')
                    || s[i] == QChar('[') || s[i] == QChar('.')
                    || s[i] == QChar(','))
				code += s[i];
	return code;
}
bool BF_debug_interp::checkIfBuildable(){
	int sum =0;
    for(int i =0; i < code.length() || sum < 0; i++)
        if(code[i] == QChar('['))
			sum++;
        else if(code[i] == QChar(']'))
			sum--;
	if(sum == 0)
		return true;
    return false;
}

void BF_debug_interp::debug()
{
    try{
        while(1){
            while(!nextInstr)
                wait(1000);
            interprete(debugging);
            nextInstr--;
        }
    } catch(std::string ex) {

    }
}
//--------------instrukcje brain fucka------------------
//
//
//
void BF_debug_interp::shiftRight(){
    if(mem_ptr + 1 == len)
        mem_ptr =0;
    else
        mem_ptr++;
}

void BF_debug_interp::shiftLeft(){
    if(mem_ptr == 0)
        mem_ptr = len-1;
    else
        mem_ptr--;
}

void BF_debug_interp::plus(){
    if(memory[mem_ptr]==255)
        memory[mem_ptr]=0;
    else
        memory[mem_ptr]++;
}

void BF_debug_interp::minus(){
    if(memory[mem_ptr]==0)
        memory[mem_ptr]=255;
    else
        memory[mem_ptr]--;
}
void BF_debug_interp::bracketLeft(){

#ifdef DBG
    printf("lewy mem_ptr=%d, code_ptr=%d\n",mem_ptr, code_ptr);
    getchar();
#endif

    if(!memory[mem_ptr]){
        int sum =0;
        for(int i =code_ptr; ; i++)
            if(code[i] == QChar('['))
                sum++;
            else if(code[i] == QChar(']') && sum)
                sum--;
            else if(code[i] == QChar(']')){
                code_ptr = i+1;
                break;
            }
    }
    else
        loop_beg.push(code_ptr);
}
void BF_debug_interp::bracketRight(){

#ifdef DBG
    printf("prawy mem_ptr=%d, code_ptr=%d\n",mem_ptr, code_ptr);
    getchar();
#endif

    if(loop_beg.empty()){
        printf("pusty stos blad");
        exit(0);
    }
    if(memory[mem_ptr] == 0)
        loop_beg.pop();
    else
        code_ptr = loop_beg.top();


#ifdef DBG
    printf("code_ptr=%d, stack_size=%d\n", code_ptr,loop_beg.size());
#endif
}

void BF_debug_interp::comma() {

#ifdef DBG
    memory[mem_ptr] = getchar();
#endif
    while(queue.empty())
        wait(1000);
    memory[mem_ptr] = queue.front();
    queue.pop();
}

void BF_debug_interp::dot(){
#ifdef DBG
    putchar(memory[mem_ptr]);
#endif
    QString str = "";//textBrowser->toPlainText();
    //std::string s(reinterpret_cast<char*>(memory));
    QChar ch = QChar(memory[mem_ptr]);//QChar(memory[mem_ptr]);
    str+=ch;//+QString::number(memory[mem_ptr]);
    emit(sign(str));
}

//-------------------- sloty----------------------
//
//
//
//
void BF_debug_interp::slot1(QString str){
    textBrowser->setText(textBrowser->toPlainText()+str);
}

void BF_debug_interp::acLabel()
{
    label->setText(QString::number(mem_ptr));
}

void BF_debug_interp::acList(int index)
{
    tabWidget->setTabText(index, QString::number(memory[mem_ptr]));
}

void BF_debug_interp::doNextInstruction()
{
    nextInstr++;
}

QChar BF_debug_interp::getInstruction() throw (const std::string){
	
	#ifdef DBG
	for(int i=0; i < 10; i++)
		if(i == mem_ptr)
			printf("v ");
		else
			printf("%-3c ", ' ');
	printf("\n");
	for(int i=0; i < 10; i++)
		printf("%-3d ", memory[i]);
	printf("\n code_ptr=%d, len=%d, por=%d\n", code_ptr, code.length(), code[code.length()]);
	#endif
	
    if(code_ptr >= (int)(code.length()-1) )
		throw (std::string)"koniec";
    return code[++code_ptr];
}

void BF_debug_interp::addInput(unsigned char znak)
{
    queue.push(znak);
}

void BF_debug_interp::setDebuggeMode(bool flag){
    debugging = flag;
}

void BF_debug_interp::interprete(bool debug = false){
	bool flag =true;
	while(flag && !debug){
		try{
            QChar c;
            if((c = getInstruction()) == QChar('+'))
					plus();
            else if(c == QChar('-'))
					minus();
            else if(c == QChar('>'))
					shiftRight();
            else if(c == QChar('<'))
					shiftLeft();
            else if(c == QChar('['))
					bracketLeft();
            else if(c == QChar(']'))
					bracketRight();
            else if(c == QChar('.'))
					dot();
            else if(c == QChar(','))
					comma();
        //emit(sign(QString("bleble")+c));
		} catch(std::string ex) {
			flag = false;
		}
	}
}

void BF_debug_interp::run(){
    if(debugging){
        nextInstr = 1;
        debug();
    }
    else
        interprete(debugging);
}

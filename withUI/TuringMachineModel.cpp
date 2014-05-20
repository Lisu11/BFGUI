#include "TuringMachineModel.h"



TuringMachineModel::TuringMachineModel(){
    alphabet="";
    states=set<string>();
    function=functionType();
    length=1000;
    tape=vector<char>();
    tape.reserve(length);
}

void TuringMachineModel::setAlphabet(string alphabet){
    sort(alphabet.begin(), alphabet.end());
    alphabet.erase( unique( alphabet.begin(), alphabet.end() ), alphabet.end() );

    string::iterator it1=this->alphabet.begin();
    string::iterator it2=alphabet.begin();

    while(it1!=this->alphabet.end()&&it2!=alphabet.end()){
        if(*it1==*it2){
            it1++;
            it2++;
        }else if(*it1>*it2){//znak napotkany w starym alfabecie jest większy, niż znak napotkany w nowym - stary należy usunąć
            function.erase(*it1);
            it1++;
        }else{//dodanie nowych znakow do funkcji na podstawie wektora stanów
            functionSubType mapa = functionSubType();
            for(set<string>::iterator it=states.begin();it!=states.end();it++){
                mapa.insert(pair<string,TuringFunctionValue>(*it,TuringFunctionValue()));
            }
            function.insert(pair<char,functionSubType>(*it2,mapa));
            it2++;
        }
    }
    //usuniecie pozostalych znakow ze starego alfabetu
    while(it1!=this->alphabet.end()){
        function.erase(*it1);
        it1++;
    }
    //dodanie pozostalych znakow z nowego alfabetu
    while(it2!=alphabet.end()){
        //uzupełnienie funkcji na podstawie wektora stanów
        functionSubType mapa = functionSubType();
        for(set<string>::iterator it=states.begin();it!=states.end();it++){
            mapa.insert( pair<string,TuringFunctionValue>( *it,TuringFunctionValue() ) );
        }
        function.insert(pair<char,functionSubType>(*it2,mapa));
        it2++;
    }

    //zastapenie alfabetu nowym
    this->alphabet=alphabet;
}

void TuringMachineModel::addState(string state){
    for(functionType::iterator it=function.begin();it!=function.end();it++){
        it->second.insert(pair<string,TuringFunctionValue>( state,TuringFunctionValue() ) );
    }
    states.insert(state);
}

void TuringMachineModel::removeState(string state){
    for(functionType::iterator it=function.begin();it!=function.end();it++){
        it->second.erase(state);
    }
}

void TuringMachineModel::setLength(int length){
    this->length=length;
}

void TuringMachineModel::setTape(int tapeBegin, string tapeString){
    vector<char>::iterator it=tape.begin();
    for(;it!=tape.begin()+tapeBegin;it++){
        *it=0;
    }
    for(string::iterator stit=tapeString.begin();stit!=tapeString.end();stit++,it++){
        *it=*stit;
    }
    for(;it!=tape.end();it++){
        *it=0;
    }
}

void TuringMachineModel::setTapePosition(int position){
    this->tapePosition=position;
}

int TuringMachineModel::getTapePosition(){
    return tapePosition;
}

void TuringMachineModel::setState(string state){
    this->state=state;
}

string TuringMachineModel::getState(){
    return state;
}





#include "CSEMachine.h"

CSEMachine :: CSEMachine(StructureList* sl, bool printExe){
	this->sl = sl;
	currEnv = 0;
	maxEnv = 0;
	init();
	done = false;
	this->printExe = printExe;
	
	if(printExe){
		cout << stateToString() << endl;
	}
}

string CSEMachine :: stateToString(){
	
	list<ControlUnit*>::iterator it;
	ostringstream temp;
	
	temp << "[";
	for (it = controlStack.begin(); it != controlStack.end(); it++){
		if(it != controlStack.begin()){
			temp << ", ";
		}
		temp << CUHelper :: getString(*it);
	}
	temp << "]";
	
	temp << " --- ";
		
	temp << "[";
	for (it = exeStack.begin(); it != exeStack.end(); it++){
		if(it != exeStack.begin()){
			temp << ", ";
		}
		temp << CUHelper :: getString(*it);
	}
	temp << "]";
	
	temp << " ~~ Env=" << currEnv;
	
	temp << " " << el.at(currEnv)->toString();
	
	return temp.str();
	
}

void CSEMachine :: init(){

	Enviornment* e0 = new Enviornment();
	el.push_back(e0);
	controlStack.push_back(new EnvCU(0));
	exeStack.push_front(new EnvCU(0));
	
	controlStack.push_back(sl->list.at(0));
	
}

void CSEMachine :: run(){
	
	while(!done){
		tick();	
	}
	
}

void CSEMachine :: tick(){
	
	switch(controlStack.back()->type){
		case STRUCTURE:
			expandStructure();
			break;
		case INTEGER:
			moveInt();
			break;
		case LAMBDA:
			moveLambda();
			break;
		case GAMMA:
			exeGamma();
			break;
		case IDENTIFIER:
			lookupId();
			break;
		case ENVIORNMENT:
			returnFromEnv();
			break;
		case BINOP:
			exeBinop();
			break;
		case UNOP:
			exeUnop();
			break;
		case TAU:
			exeTau();
			break;
		case Y:
			moveY();
			break;
		case BETA:
			exeBeta();
			break;
		case STRING:
			moveString();
			break;
		case BOOLEAN:
			moveBoolean();
			break;
		case TUPLE:
			move();
			break;
		case DUMMY:
			move();
			break;
		default:
			cout << "Unexpected ControlUnit type : " << controlStack.back()->type << endl;
			exit(EXIT_FAILURE);
	}
	
	if(printExe){
		cout << stateToString() << endl;
	}
	
}

void CSEMachine :: expandStructure(){

	ControlStructure* cs = (ControlStructure*)controlStack.back();
	
	controlStack.pop_back();
	
	expandStructure(cs);
	
}

void CSEMachine :: expandStructure(ControlStructure* cs){

	vector<ControlUnit*>::iterator it;
	for (it = cs->units.begin(); it != cs->units.end(); it++){
		controlStack.push_back(*it);
	}
	
}

void CSEMachine :: moveInt(){

	IntegerCU* icu = (IntegerCU*)controlStack.back();
	
	controlStack.pop_back();
	exeStack.push_front(icu);
	
}

void CSEMachine :: moveLambda(){

	LambdaCU* lcu = (LambdaCU*)controlStack.back();
	lcu->currEnv = currEnv;
	
	controlStack.pop_back();
	exeStack.push_front(lcu);
	
}

void CSEMachine :: exeGamma(){
	
	ControlUnit* cu = exeStack.front();
	
	switch(cu->type){
		case LAMBDA:
			exeGammaOnLambda();
			break;
		case FUNCTION:
			exeGammaOnFunction();
			break;
		case Y:
			exeGammaOnY();
			break;
		case ETA:
			exeGammaOnEta();
			break;
		case TUPLE:
			exeGammaOnTuple();
			break;
		default:
			cout << "Unexpected ControlUnit for gamma execution : " << controlStack.back()->type << endl;
			exit(EXIT_FAILURE);
	}
	
}

void CSEMachine :: exeGammaOnLambda(){
	
	GammaCU* gcu = (GammaCU*)controlStack.back();
	LambdaCU* lcu = (LambdaCU*)exeStack.front();
	controlStack.pop_back();
	exeStack.pop_front();
	
	Enviornment* newEnv = new Enviornment(el.at(lcu->currEnv));
	el.push_back(newEnv);
	
	maxEnv++;
	currEnv = maxEnv;
	
	bindVariables(lcu, newEnv);
	
	controlStack.push_back(new EnvCU(currEnv));
	exeStack.push_front(new EnvCU(currEnv));
	
	expandStructure(sl->list.at(lcu->lambdaNum));
	
}

void CSEMachine :: bindVariables(LambdaCU* lcu, Enviornment* newEnv){
	
	if(lcu->bindingVars.size()==1){
		string varStr = lcu->bindingVars.at(0);
		newEnv->addBinding(varStr, exeStack.front());
		exeStack.pop_front();
	}
	else{
		
		TupleCU* tcu = (TupleCU*)exeStack.front();
		exeStack.pop_front();
		
		for(int i = 0; i < lcu->bindingVars.size(); i++){
			newEnv->addBinding(lcu->bindingVars.at(i), tcu->list.at(i));
		}
		
	}
	
}

void CSEMachine :: exeGammaOnFunction(){
	
	GammaCU* gcu = (GammaCU*)controlStack.back();
	FunctionCU* fcu = (FunctionCU*)exeStack.front();
	controlStack.pop_back();
	
	if(fcu->nameIs("Print")){
		callPrint();
	}
	else if(fcu->nameIs("Stem")){
		callStem();
	}
	else if(fcu->nameIs("Stern")){
		callStern();
	}
	else if(fcu->nameIs("Conc1")){
		callConcP1();
	}
	else if(fcu->nameIs("Conc2")){
		callConcP2();
	}
	else if(fcu->nameIs("Order")){
		callOrder();
	}
	else if(fcu->nameIs("ItoS")){
		callItoS();
	}
	else if(fcu->nameIs("Istuple")){
		callIstuple();
	}
	else if(fcu->nameIs("Isfunction")){
		callIsfunction();
	}
	else if(fcu->nameIs("Isdummy")){
		callIsdummy();
	}
	else if(fcu->nameIs("Isstring")){
		callIsstring();
	}
	else if(fcu->nameIs("Isinteger")){
		callIsinteger();
	}
	else if(fcu->nameIs("Istruthvalue")){
		callIstruthvalue();
	}
	else{
		cout << "Unknown function : " << fcu->name << endl;
		exit(EXIT_FAILURE);	
	}
	
}

void CSEMachine :: callPrint(){
	
	exeStack.pop_front();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new DummyCU());
	
	output << CUHelper :: getString(cu);
	
}

void CSEMachine :: lookupId(){

	IdCU* icu = (IdCU*)controlStack.back();
	controlStack.pop_back();
	
	if(icu->nameIs("Print")){
		exeStack.push_front(new FunctionCU("Print"));	
	}
	else if(icu->nameIs("Stem")){
		exeStack.push_front(new FunctionCU("Stem"));	
	}
	else if(icu->nameIs("Stern")){
		exeStack.push_front(new FunctionCU("Stern"));	
	}
	else if(icu->nameIs("Conc")){
		exeStack.push_front(new FunctionCU("Conc1"));	
	}
	else if(icu->nameIs("Order")){
		exeStack.push_front(new FunctionCU("Order"));	
	}
	else if(icu->nameIs("ItoS")){
		exeStack.push_front(new FunctionCU("ItoS"));	
	}
	else if(icu->nameIs("Istuple")){
		exeStack.push_front(new FunctionCU("Istuple"));	
	}
	else if(icu->nameIs("Isfunction")){
		exeStack.push_front(new FunctionCU("Isfunction"));	
	}
	else if(icu->nameIs("Isdummy")){
		exeStack.push_front(new FunctionCU("Isdummy"));	
	}
	else if(icu->nameIs("Isstring")){
		exeStack.push_front(new FunctionCU("Isstring"));	
	}
	else if(icu->nameIs("Isinteger")){
		exeStack.push_front(new FunctionCU("Isinteger"));	
	}
	else if(icu->nameIs("Istruthvalue")){
		exeStack.push_front(new FunctionCU("Istruthvalue"));	
	}
	else{
		exeStack.push_front(el.at(currEnv)->getBinding(icu->name));
	}
}

void CSEMachine :: returnFromEnv(){
	
	//Pop env off of exe Stack
	if(exeStack.front()->type == ENVIORNMENT){
		exeStack.pop_front();
	}
	else{
		ControlUnit* cu = exeStack.front();
		exeStack.pop_front();
		exeStack.pop_front();
		exeStack.push_front(cu);
	}
	
	//Pop env off controlStack and adjust currEnv
	controlStack.pop_back();
	//EnvCU* ecu1 = (EnvCU*)controlStack.back();
	if(currEnv == 0){
		done = true;
	}
	else{
		
		list<ControlUnit*>::iterator it;
		
		for (it = exeStack.begin(); it != exeStack.end(); it++){
			if((*it)->type == ENVIORNMENT){
				currEnv = ((EnvCU*)(*it))->envNumber;
				//cout << "CHANGING ENV TO " << currEnv << endl;
				break;
			}
		}
	}

}

void CSEMachine :: exeBinop(){
	
	BinopCU* bcu = (BinopCU*)controlStack.back();
	controlStack.pop_back();
	
	ControlUnit* cu1 = exeStack.front();
	exeStack.pop_front();
	ControlUnit* cu2 = exeStack.front();
	exeStack.pop_front();
	
	if(bcu->opIs("+")){
		exeStack.push_front(new IntegerCU(CUHelper :: add(cu1, cu2)));
	}
	else if(bcu->opIs("-")){
		exeStack.push_front(new IntegerCU(CUHelper :: subtract(cu1, cu2)));
	}
	else if(bcu->opIs("*")){
		exeStack.push_front(new IntegerCU(CUHelper :: multiply(cu1, cu2)));
	}
	else if(bcu->opIs("/")){
		exeStack.push_front(new IntegerCU(CUHelper :: divide(cu1, cu2)));
	}
	else if(bcu->opIs("**")){
		exeStack.push_front(new IntegerCU(CUHelper :: power(cu1, cu2)));
	}
	else if(bcu->opIs("aug")){
		exeStack.push_front(CUHelper :: aug(cu1, cu2));
	}
	else if(bcu->opIs("or")){
		exeStack.push_front(new BooleanCU(CUHelper :: logicalOr(cu1, cu2)));
	}
	else if(bcu->opIs("&")){
		exeStack.push_front(new BooleanCU(CUHelper :: logicalAnd(cu1, cu2)));
	}
	else if(bcu->opIs("gr")){
		exeStack.push_front(new BooleanCU(CUHelper :: gr(cu1, cu2)));
	}
	else if(bcu->opIs("ge")){
		exeStack.push_front(new BooleanCU(CUHelper :: ge(cu1, cu2)));
	}
	else if(bcu->opIs("ls")){
		exeStack.push_front(new BooleanCU(CUHelper :: ls(cu1, cu2)));
	}
	else if(bcu->opIs("le")){
		exeStack.push_front(new BooleanCU(CUHelper :: le(cu1, cu2)));
	}
	else if(bcu->opIs("eq")){
		exeStack.push_front(new BooleanCU(CUHelper :: eq(cu1, cu2)));
	}
	else if(bcu->opIs("ne")){
		exeStack.push_front(new BooleanCU(CUHelper :: ne(cu1, cu2)));
	}
	else{
		cout << "Unexpected Binop Operator" << endl;
		exit(EXIT_FAILURE);
	}
	
}

void CSEMachine :: exeTau(){
	
	TauCU* tcu = (TauCU*)controlStack.back();
	controlStack.pop_back();
	
	TupleCU* tupcu = new TupleCU();
	
	for(int i = 0; i < tcu->num; i++){
		tupcu->insert(exeStack.front());
		exeStack.pop_front();
	}
	
	exeStack.push_front(tupcu);
	
}

void CSEMachine :: moveY(){
	
	exeStack.push_front(controlStack.back());
	controlStack.pop_back();
	
}

void CSEMachine :: exeGammaOnY(){
	
	exeStack.pop_front(); //Remove Y
	
	GammaCU* gcu = (GammaCU*)controlStack.back();
	LambdaCU* lcu = (LambdaCU*)exeStack.front();
	controlStack.pop_back();
	exeStack.pop_front();
	
	EtaCU* ecu = new EtaCU(lcu);
	
	exeStack.push_front(ecu);
}

void CSEMachine :: exeGammaOnEta(){
	
	EtaCU* ecu = (EtaCU*)exeStack.front();
	controlStack.push_back(new GammaCU());
	
	//EXP IDEA
	ecu->recLambda->currEnv = currEnv;
	
	exeStack.push_front(ecu->recLambda);

}

void CSEMachine :: exeBeta(){
	
	BooleanCU* bcu = (BooleanCU*)exeStack.front();
	exeStack.pop_front();
	
	controlStack.pop_back(); //Remove beta
	
	if(bcu->value == true){
		controlStack.pop_back();
	}
	else{
		ControlUnit* cu = controlStack.back();
		controlStack.pop_back();
		controlStack.pop_back();
		controlStack.push_back(cu);
		
	}
	
	
}

void CSEMachine :: moveString(){
	
	exeStack.push_front(controlStack.back());
	controlStack.pop_back();
	
}

void CSEMachine :: moveBoolean(){
	
	exeStack.push_front(controlStack.back());
	controlStack.pop_back();
	
}

void CSEMachine :: callStem(){
	
	exeStack.pop_front();
	
	StringCU* str = (StringCU*)exeStack.front();
	exeStack.pop_front();
	
	StringCU* stem = new StringCU(str->value.substr(0,1));
	exeStack.push_front(stem);
	
}

void CSEMachine :: callStern(){
	
	exeStack.pop_front();
	
	StringCU* str = (StringCU*)exeStack.front();
	exeStack.pop_front();
	
	StringCU* stern = new StringCU(str->value.substr(1,str->value.length()));
	exeStack.push_front(stern);
	
}

void CSEMachine :: callConcP1(){
	
	exeStack.pop_front();
	
	StringCU* str = (StringCU*)exeStack.front();
	exeStack.pop_front();
	
	FunctionCU* conc2 = new FunctionCU("Conc2");
	conc2->dataStr = str->value;
	
	exeStack.push_front(conc2);
	
}

void CSEMachine :: callConcP2(){
	
	FunctionCU* conc2 = (FunctionCU*)exeStack.front();
	exeStack.pop_front();
	
	StringCU* str = (StringCU*)exeStack.front();
	exeStack.pop_front();
	
	StringCU* ans = new StringCU(conc2->dataStr + str->value);
	
	exeStack.push_front(ans);
	
}

void CSEMachine :: exeGammaOnTuple(){
	
	controlStack.pop_back();
	
	TupleCU* tup = (TupleCU*)exeStack.front();
	exeStack.pop_front();
	
	IntegerCU* num = (IntegerCU*)exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(tup->list.at(num->num-1)); //-1 for 1 index in rpal???
	
}

void CSEMachine :: callOrder(){
	
	exeStack.pop_front();
	
	TupleCU* tup = (TupleCU*)exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new IntegerCU(tup->list.size()));
	
}
	
void CSEMachine :: callItoS(){
	
	exeStack.pop_front();
	
	IntegerCU* icu = (IntegerCU*)exeStack.front();
	exeStack.pop_front();
	
	ostringstream temp;
	temp << icu->num;
	
	exeStack.push_front(new StringCU(temp.str()));
	
}

void CSEMachine :: callIstuple(){
	
	exeStack.pop_front();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new BooleanCU(cu->type == TUPLE));
	
}

void CSEMachine :: callIsfunction(){
	
	exeStack.pop_front();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new BooleanCU(cu->type == LAMBDA));
	
}

void CSEMachine :: callIsdummy(){
	
	exeStack.pop_front();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new BooleanCU(cu->type == DUMMY));
	
}

void CSEMachine :: callIsstring(){
	
	exeStack.pop_front();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new BooleanCU(cu->type == STRING));
	
}

void CSEMachine :: callIsinteger(){
	
	exeStack.pop_front();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new BooleanCU(cu->type == INTEGER));
	
}

void CSEMachine :: callIstruthvalue(){
	
	exeStack.pop_front();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	exeStack.push_front(new BooleanCU(cu->type == BOOLEAN));
	
}

void CSEMachine :: exeUnop(){
	
	BinopCU* bcu = (BinopCU*)controlStack.back();
	controlStack.pop_back();
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	if(bcu->opIs("not")){
		exeStack.push_front(new BooleanCU(CUHelper :: logicalNot(cu)));
	}
	else if(bcu->opIs("neg")){
		exeStack.push_front(new IntegerCU(CUHelper :: neg(cu)));
	}
	else{
		cout << "Unexpected Unop Operator" << endl;
		exit(EXIT_FAILURE);
	}
	
}

void CSEMachine :: move(){
	
	exeStack.push_front(controlStack.back());
	controlStack.pop_back();
	
}
	
	

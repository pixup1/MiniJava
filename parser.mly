%{
  open LMJ
  let swap = List.map (fun (x, y) -> (y, x))
%}

%token <int32> INT_CONST
%token <float> FLOAT_CONST
%token <bool> BOOL_CONST
%token INTEGER BOOLEAN FLOAT
%token <string Location.t> IDENT
%token CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS RETURN
%token PLUS MINUS TIMES DIV MOD NOT LT GT LEQ GEQ EQ NEQ AND OR ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN ORBITWISE XOR ANDBITWISE OPSHIFTLEFT OPSHIFTRIGHT 
%token INC
%token COMMA SEMICOLON
%token ASSIGN
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token THIS NEW DOT LENGTH
%token SYSO
%token IF ELSE WHILE FOR BREAK CONTINUE
%token EOF

%left AND ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN OR ORBITWISE XOR ANDBITWISE OPSHIFTLEFT OPSHIFTRIGHT 
%nonassoc EQ NEQ
%nonassoc LT GT LEQ GEQ
%left PLUS MINUS 
%left TIMES DIV MOD
%nonassoc NOT INC
%nonassoc DOT LBRACKET

%start program

%type <LMJ.program> program

%%

program:
| m = main_class d = defs EOF
   {
     let c, a, i = m in
     {
       name = c;
       defs = d;
       main_args = a;
       main = i
     }
   }

main_class:
| CLASS c = IDENT
   LBRACE
   PUBLIC STATIC VOID MAIN LPAREN STRING LBRACKET RBRACKET a = IDENT RPAREN
   LBRACE
   i = list(instruction)
   RBRACE
   RBRACE
   { (c, a, IBlock i) }

defs:
| c = list(clas)
   { c }

clas:
| CLASS name = IDENT e = option(preceded(EXTENDS, IDENT))
   LBRACE
   a = list(pair(typ, terminated(IDENT, SEMICOLON)))
   m = list(metho)
   RBRACE
   {
     name,
     {
       extends = e;
       attributes = swap a;
       methods = m;
     }
   }

metho:
| PUBLIC t = typ name = IDENT
   LPAREN
   f = separated_list(COMMA, pair(typ, IDENT))
   RPAREN
   LBRACE
   ds = declarations_and_statements
   RETURN e = expression SEMICOLON
   RBRACE
   {
     let d, s = fst ds, snd ds in
     name,
     {
       formals = swap f;
       result  = t;
       locals  = d;
       body    = s;
       return  = e;
     }
   }

declarations_and_statements:
| t = typ id = IDENT ASSIGN e = expression SEMICOLON r = declarations_and_statements
    {
      let d, s = r in
      ((id, t) :: d,
       ISetVar(id, e) :: s)
    }
| t = typ id = IDENT SEMICOLON r = declarations_and_statements
   {
     let d, s = r in
     ((id, t) :: d, s)
   }
| s = list(instruction)
   { ([], s) }

expression:
|  e = raw_expression
   { Location.make $startpos $endpos e }
| LPAREN e = expression RPAREN
   { e }

raw_expression:
| i = INT_CONST
   { EConst (ConstInt i) }

| b = BOOL_CONST
   { EConst (ConstBool b) }

| f = FLOAT_CONST
   { EConst (ConstFloat f) }

| id = IDENT
   { EGetVar id }

| e1 = expression op = binop e2 = expression
   { EBinOp (op, e1, e2) }

| o = expression DOT c = IDENT LPAREN actuals = separated_list(COMMA, expression) RPAREN
   { EMethodCall (o, c, actuals) }

| a = expression LBRACKET i = expression RBRACKET
   { EArrayGet (a, i) }

| NEW INTEGER LBRACKET e = expression RBRACKET
   { EArrayAlloc e }

| a = expression DOT LENGTH
   { EArrayLength a }

| THIS
   { EThis }

| NEW id = IDENT LPAREN RPAREN
   { EObjectAlloc id }

| NOT e = expression
   { EUnOp (UOpNot, e) }

| id = IDENT INC
   { EIncPost id } 

| INC id = IDENT
   { EIncPre id }


%inline binop:
| PLUS  { OpAdd }
| MINUS { OpSub }
| TIMES { OpMul }
| DIV   { OpDiv }
| MOD   { OpMod }
| LT    { OpLt }
| GT    { OpGt }
| LEQ   { OpLeq }
| GEQ   { OpGeq }
| EQ    { OpEq }
| NEQ   { OpNeq }
| AND   { OpAnd }
| OR    { OpOr }
| ORBITWISE { OpOrBitwise }
| XOR   { OpXor }
| ANDBITWISE { OpAndBitwise }
| OPSHIFTLEFT { OpShiftLeftBitwise }
| OPSHIFTRIGHT { OpShiftRightBitewise }
| ADDASSIGN { OpAddAssign }
| SUBASSIGN { OpSubAssign }
| MULASSIGN { OpMulAssign }
| DIVASSIGN { OpDivAssign }
| MODASSIGN { OpModAssign }

instruction:
| b = block
   { b }
| id = IDENT ADDASSIGN e = expression SEMICOLON
   {
     let lhs =
       Location.make (Location.startpos id) (Location.endpos id) (EGetVar id)
     in
     IExpr (Location.make $startpos $endpos (EBinOp (OpAddAssign, lhs, e)))
   }

| id = IDENT ASSIGN e = expression SEMICOLON
   { ISetVar (id, e) }

| a = IDENT LBRACKET i = expression RBRACKET ASSIGN e = expression SEMICOLON
   { IArraySet (a, i, e) }

| SYSO LPAREN e = expression RPAREN SEMICOLON
   { ISyso e }

| IF LPAREN c = expression RPAREN i1 = instruction ELSE i2 = instruction
   { IIf (c, i1, i2) }

| IF LPAREN c = expression RPAREN i = instruction
   { IIf (c, i, IBlock []) }

| WHILE LPAREN c = expression RPAREN i = instruction
   { IWhile (c, i) }

| FOR LPAREN id1 = IDENT ASSIGN e1 = expression SEMICOLON c = expression SEMICOLON id2 = IDENT ASSIGN e2 = expression RPAREN i = instruction
   { IFor (ISetVar (id1, e1), c, ISetVar (id2, e2), i) }

| e = expression SEMICOLON
   { IExpr e }

| BREAK SEMICOLON
   { IBreak }

| CONTINUE SEMICOLON
   { IContinue }

block:
| LBRACE is = list(instruction) RBRACE
   { IBlock is }

typ:
| INTEGER
   { TypInt }
| FLOAT
   { TypFloat }
| BOOLEAN
   { TypBool }
| INTEGER LBRACKET RBRACKET
   { TypIntArray }
| FLOAT LBRACKET RBRACKET
   { TypFloatArray }
| id = IDENT
   { Typ id }

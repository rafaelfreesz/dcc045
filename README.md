# DCC045
### Commit 05/11/2022:

<ul>
  <li>Fixed Lexical Analyzer class (Now it uses .cpp);</li>
  <li>Using extern "C";</li>
  <li>compile with "g++ *.c *.h *.cpp  -o arq".</li>
</ul>
### Commit 11/10/2022: Second correction of AFD scheme:
<ul>
    <li>First prototype implementation</li>
    <li>Created SEMICOLON (;) state</li>
</ul>

### Commit 3: Second correction of AFD scheme:
<ul>
  <li>Real number leads to NUMFLOAT;</li>
  <li>State q49 changed to "Malformed number" error; </li>
  <li>State 32 removed.</li>
</ul>

### Commit 2: First correction of AFD scheme:

<ul>
  <li>Improved tokens names (<a href="https://www.englishexperts.com.br/caracteres-especiais-e-de-pontuacao-em-ingles/">Font</a>);</li>
  <li>Created INT, DOUBLE and REAL tokens for NUMBER;</li>
  <li>"EOF Exception" label changed to "Ret Lexic Error (Unexpected EOF)";</li>
  <li>Created Lexic Error state for "Unexpected Entry";</li>
  <li>Removed wrongs character pumpings for CHAR LITERALs;</li>
  <li>Alowed only \n, \r ,\f, \t, \a, \b, \o, \v, \\, \' and \" for LITERAL C representations with '\' (<a href="https://stackoverflow.com/questions/18018264/how-do-i-declare-backslash-constant-character-in-c">Font</a>);</li>
  <li>States renamed for better organization.</li>
</ul> 

### Commit 1: AFD scheme presented at 09/29/2022

  <ul>
  <li> TODO: </li>
  <ol>
      <li>Improve tokens names ({,},(,),[,],=,==,>,:,|,||,&,&&,->);</li>
      <li>Make REAL numbers recognition;</li>
      <li>Differentiate of numbers in INT, DOUBLE or REAL;</li>
      <li>Change "EOF Exception" states label to "Lexic Error";</li>
      <li>q47 pumps only "Others";</li>
      <li>Change q49->q47 transition to "Others" carachters;</li>
      <li>q50 does not pump;</li>
      <li>Correct arc direction on q0->q11</li>      
  </ol>

<ul>

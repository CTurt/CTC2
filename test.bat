make
pause

CTC2 main.c -c -o main.c.ctc2
CTC2 ctc2.c -c -o ctc2.c.ctc2
pause

CTC2 main.c.ctc2 -d -o main_decompressed.c
pause
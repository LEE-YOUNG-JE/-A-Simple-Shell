# linux-A-Simple-Shell

# 과제
1) 사용자 명령을 받아들이고 각 명령을 별도의 프로세스에서 실행하는 간단한 셸 인터페이스(osh) 설계하는 것이다.

2) 추가 구현:
argument handling:
e.g.) ps -ael

background execution:
e.g.) firefox &

 history: print out five recent commands:
e.g.) ps, ls –l, top, cal, who, date
5 ls –l
4 top
3 cal
2 who
1 date

!!: the most recent command in the history is executed

!N: the N’th command in the history is executed

exit: exit the shell

## DS_project2_2020_2
### 2020-2 Data Structure Project #2

### Due date: 2020/11/6 23h 59m 59s.

#### 본 프로젝트는 상품 추천 프로그램을 구현하는 것으로 상세한 설명은 프로젝트 문서와 다음 설명을 참고한다.
##### 본 프로젝트에서는 FP-Growth와 B+-Tree를 이용하여 상품 추천 프로그램을 구현한다. 이 프로그램은 장바구니 데이터에서 같이 구매한 상품들을 받아 FP-Growth를 구축한다. FP-Growth는 상품들의 연관성을 Tree 구조로 저장하고 있는 FP-Tree와 상품별 빈도수 및 정보, 해당 상품과 연결된 FP-Tree의 상품 노드들을 관리하는 Header Table로 구성된다. FP-Growth 구축 단계에서 연관된 상품들을 묶은 Frequent Pattern의 결과는 result.txt에 빈도수, 상품 순으로 저장한다. Frequent Pattern들이 저장된 result.txt는 BTLOAD 명령어를 통해 빈도수를 기준으로 B+-Tree에 저장이 된다. B+-Tree는 IndexNode와 DataNode로 구성된다. IndexNode는 DataNode를 찾기 위한 Node이고 DataNode는 해당 빈도수를 가지는 Frequent Pattern들이 저장된 Node이다. 채점 기준은 FP-Tree와 Header Table 생성 및 연결과 B+-Tree이며, FP-Growth의 결과인 result.txt(Frequent Pattern)는 가산점으로 부여된다.

![image](https://user-images.githubusercontent.com/50433145/95163832-b0327700-07e3-11eb-8ece-b1a71aaf3b49.png)

## <u>**Notice**</u>
### Notice !! 윈도우에서 리눅스로 단순 파일 복사 및 드래그는 파일 인코딩 변환 문제가 발생 할 수 있으니 
### 반드시 리눅스 환경에서 파일을 재생성 후 테스트 바랍니다!!
### Notice !!설계와 실습을 모두 수강하시는 분은 실습 과제제출란에만 제출 해주시면 됩니다 !!
### Notice !!log.txt의 출력 포맷에서 모든 구분자는 '\t'이 아닌 스페이스바(' ')로 하시면 됩니다. !!
### Notice !!10/06 15시에 소스코드 수정이 있으니 이전에 다운받은 학생들은 다시 다운받아 구현하세요 !!
--------------------------




### 1. 프로젝트 문서 및 소스코드 수정사항

#### [2020_DS_Project2_ver1.pdf](https://github.com/DSLDataStorage/DS_Project_2_2020_2/files/5331741/2020_DS_Project2_ver1.pdf)

```
10/06 - ver1 업로드
```


### 2. 자주들어오는 질문 

**Q. command.txt는 제공하지 않나요?**  
A. 네, 윈도우와 리눅스 인코딩 호환 문제로 따로 제공하지 않습니다.  

**Q. market.txt와 result.txt는 제공하지 않나요?**

A. testcase와 result로 제공됩니다. 각 번호에 맞게 짝을 지어 파일 명을 변경 후 사용하세요.
만약 리눅스 인코딩 호환 문제로 인식을 못할 수 있으니 확인을 하시고 호환 문제 발생 시 새 문서를 만들고 복사해서 사용하세요.

--------------------------
### Knowledge 
##### 아래 명령어 예시에서 앞의 $ 로 시작되는 부분은 명령어 입력 부분이고, 그 외 는 출력 부분임
##### 리눅스 명령어 요약
1. ls  :  list로 현재 작업중인 디렉토리의 파일 및 포함된 디렉토리 목록들을 표시 ( -a, -l 속성으로 자세한 출력 가능)
2. pwd  :  print working directory로 현재 작업중인 디렉토리의 절대경로 위치 출력
3. cd  : change directory로 디렉토리 를 변경( . : 현재 디렉토리, .. : 상위 디렉토리 ) 
```
$ ls
Documents Download
$ ls -l
drwxr-xr-x 2 user user     4096 Oct 05  2020 Documents
drwxr-xr-x 2 user user     4096 Oct 05  2020 Downloads
$ pwd
/home/user
$ cd Download
$ pwd
/home/user/Downloads
```

### requirement
##### 먼저 해당 github에 저장되어 있는 base 코드를 다운받는다.
```
$ sudo apt-get install git
$ git clone https://github.com/DSLDataStorage/DS_Project_2_2020_2.git
```

### how to compile this project
##### make명령어 실행 후 ls명령어를 통해 해당 디렉토리를 확인해 보면 run 이라는 파일이 생긴것을 확인 할 수 있다. 
```
$ make
g++ -std=c++11 -g -o run HeaderTable.cpp FPNode.cpp BpTree.cpp Manager.cpp main.cpp FPGrowth.cpp BpTree.h Manager.h FrequentPatternNode.h BpTreeNode.h FPGrowth.h BpTreeIndexNode.h HeaderTable.h FPNode.h BpTreeDataNode.h

$ ls
BpTree.cpp BpTreeNode.h FPNode.cpp main.cpp market.txt BpTreeDataNode.h command.txt FPNode.h makefile BpTree.h FPGrowth.cpp HeaderTable.cpp Manager.cpp FrequentPatternNode.h BpTreeIndexNode.h FPGrowth.h HeaderTable.h Manager.h **run**
```
### how to run code
##### ./(생성된 실행파일) 의 형식으로 생성된 run 실행파일을 실행한다.
##### 실행하면 결과로 result.txt파일과 log.txt파일이 생성되면서 결과가 result.txt와 log.txt에 저장된다. 
```
$ ./run
$ cat log.txt
==> command 1) LOAD
Success
```

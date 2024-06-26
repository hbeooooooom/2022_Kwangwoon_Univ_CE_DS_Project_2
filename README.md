## DS_Project2_2022_2
### 2022-2 Data Structure Project #2

##### 본 프로젝트에서는 FP-Growth와 B+-Tree를 이용하여 상품 추천  프로그램을 구현한다. 
이 프로그램은 장바구니 데이터에서 같이 구매한 상품들을 받아 FP-Growth를 구축한다. FP-Growth는 상 
품들의 연관성을 Tree 구조로 저장하고 있는 FP-Tree와 상품별 빈도수 및 정보, 해당 상품과 연결 
된 FP-Tree의 상품 노드들을 관리하는 Header Table로 구성된다. FP-Growth 구축 단계에서 연 
관된 상품들을 묶은 Frequent Pattern들은 SAVE 명령어를 통해 result.txt에 빈도수, 상품 순으로 
저장한다. Frequent  Pattern들이  저장된  result.txt는 BTLOAD  명령어를  통해  빈도수를  기준으로 
B +-Tree에 저장이 된다. B+-Tree는 IndexNode와 DataNode로 구성된다. IndexNode는 DataNode 
를 찾기 위한 Node이고 DataNode는 해당 빈도수를 가지는 Frequent Pattern들이 저장된 Node이 
다

![그림1](https://user-images.githubusercontent.com/50433145/195530408-8f50eb4a-1c97-4ea7-9479-aee636c1362c.jpg)

![1](https://github.com/hbeooooooom/2022_Kwangwoon_Univ_CE_DS_Project_2/blob/main/readmdpng/1.png)

☐ Program implementation 
1) FP-Growth
- 주어진 market.txt에 저장된 데이터를 이용하여 구축한다. market.txt에서 같이 구매한 물품 
은 줄 단위로 구분되어 있다.
-  프로그램  구현  시  주어진  FPNode  클래스를  통해  FP-Tree를  구현하고  주어진  Header 
Table 클래스를 통해 Header Table을 구현한다.
- 상품 정보는 항상 고유하며, 소문자로 표기한다고 가정한다.
- FP-Growth의 threshold 값은 고정되어 있지 않으며 멤버 변수로 변경할 수 있다. 
∙threshold 값은 2 이상으로 설정한다고 가정한다
- Header Table, FP-Tree, B+-Tree의 구축 방법과 조건에 대한 자세한 설명은 아래에서 추가 
설명한다

![2](https://github.com/hbeooooooom/2022_Kwangwoon_Univ_CE_DS_Project_2/blob/main/readmdpng/2.png)

2) Header Table
- Header Table은 인덱스 테이블(indexTable)과 데이터 테이블(dataTable)로 구성한다. 
- Header Table에는 threshold보다 작은 상품들도 저장한다.
- 인덱스 테이블은 빈도수를 기준으로 정렬된 상품들을 저장하는 변수다. 이 변수는 아래와 같
이 STL의 list를 사용하며 list에는 pair를 통해 빈도수와 상품명을 저장한다. 
⦁list<pair<int, string>> indexTable
- 인덱스 테이블에서는 빈도수를 기준으로 오름차순과 내림차순으로 정렬을 할 수 있는 함수가 
구현되어야 하며, 이는 list에서 제공되는 sort 함수를 이용하여 구현한다.
- 데이터 테이블은 상품명과 상품에 연결되는 포인터를 저장하는 변수다. 이 변수는 아래와 같
이  STL의  map  컨테이너  형태로  key와  value로  상품명과  상품에  연결되는  FP-Tree의 
Node (FPNode) 포인터를 저장한다.
⦁map<string, FPNode*> dataTable
3) FP-Tree
- FP-Tree 클래스는 따로 생성하지 않고 FPNode를 이용하여 구축한다. 
- root에서 자식 노드를 제외한 변수들은 NULL 값을 갖는다.
- 자식  노드들은  아래와  같이  map  컨테이너  형태로  저장하며, 부모  노드를  가리키는  노드가 
존재한다. key의 string은 상품명을 저장하고 value의 FPNode*는 해당 상품의 빈도수 정보 
및 연결된 Node 정보들을 저장한다.
⦁map<string, FPNode*> children
- FP-Tree에 저장된 노드들은 Header Table에서 같은 상품 노드들끼리 연결되어야 한다.

![3](https://github.com/hbeooooooom/2022_Kwangwoon_Univ_CE_DS_Project_2/blob/main/readmdpng/3.png)

- FP-Tree에서는 각각 연결된 연관 상품에 따라 빈도수를 정확히 설정해야 한다.
- FP-Tree에  연결되는  상품  순서는  빈도수를  기준으로  내림차순으로  결정이  되며,  Header 
Table의 정렬 기준에 따라 결정이 된다.
- 빈도수가 같은 경우 Header Table에서 indexTable의 정렬 기준에 따라 결정이 된다.
- children에 저장되는 데이터는 상품명과 상품 노드 (FPNode)이며 상품 노드에는 빈도수 정보, 
부모 노드 정보, 자식 노드 정보가 저장되어야 한다.
4) B+-Tree
- result.txt에 저장된 데이터를 이용하여 구축한다.
-  result.txt는  빈도수가  제일  처음으로  주어지며  그  뒤에  “\t”을  구분자로  하여  연관된  상품들 
(Frequent Patterns)을 저장한 파일이다.
- B+-Tree는 그림 4와 같이 빈도수를 기준으로 정렬된다.
-  B+-Tree는  인덱스  노드  (BpTreeIndexNode)와  데이터  노드  (BpTreeDataNode)로  구성되며, 
각 노드 클래스는 B+-tree 노드 클래스 (BpTreeNode)를 상속받는다.
- 데이터  노드는  단말  노드로, 해당  빈도수에  속하는  Frequent  Pattern이 저장된 
FrequentPatternNode를 아래와 같이 map 컨테이너 형태로 가지고 있으며 가장 왼쪽 자식을 
가리키는 포인터(pMostLeftChild)를 따로 가지고 있다.
⦁map<int, FrequentPatternNode*> mapData
- B+-Tree의 차수 ORDER(m)는 고정되어 있지 않으며 멤버 변수로 변경할 수 있다.

![4](https://github.com/hbeooooooom/2022_Kwangwoon_Univ_CE_DS_Project_2/blob/main/readmdpng/4.png)

5) FrequentPatternNode
-  FrequentPatternNode는  Frequent  Pattern  정보를  아래와  같이  multimap  컨테이너  형태로  
가지고 있다.
⦁multimap<int, set<string>> FrequentPatternList
-  각  mapData의  빈도수에  해당하는  Frequent  Pattern의  정보를  저장하고  있어야  하며  key와 
value로 Frequent Pattern의 길이와 Frequent Pattern의 원소를 저장해야 한다.
- Frequent Pattern의 원소는 아래와 같이 STL의 set 컨테이너 형태로 가지고 있다. set에는 원 
소에 해당하는 상품명이 저장돼야 한다.
⦁set<string> item
- Frequent Pattern 중 공집합 이거나 원소가 하나인 집합은 저장하지 않는다.

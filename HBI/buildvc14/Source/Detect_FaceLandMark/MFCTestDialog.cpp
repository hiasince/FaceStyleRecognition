// MFCTestDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Detect_FaceLandMark.h"
#include "MFCTestDialog.h"
#include "afxdialogex.h"
#include <string>
using namespace std;

// CMFCTestDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMFCTestDialog, CDialog)

CMFCTestDialog::CMFCTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CMFCTestDialog::~CMFCTestDialog()
{
}

void CMFCTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMFCTestDialog, CDialog)
	ON_BN_CLICKED(btn_faceStyle, &CMFCTestDialog::OnBnClickedfacestyle)
	ON_BN_CLICKED(btn_Animal, &CMFCTestDialog::OnBnClickedAnimal)
	ON_BN_CLICKED(btn_change, &CMFCTestDialog::OnBnClickedchange)
END_MESSAGE_MAP()


// CMFCTestDialog 메시지 처리기입니다.


void CMFCTestDialog::OnBnClickedfacestyle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 얼굴형 정보 추가하는 부분
	string temp = "얼굴형\n\n";
	switch (faceData[0]) {
	case 1:
		temp += "둥근 얼굴 원(圓)자형 : 둥근 얼굴은 살집이 풍만하고 혈색이 좋다.명랑하고 활동적이며 추진력이 강한 성격으로 재물과 인연이 있다.잘 돌아다니는 성격으로 고향을 떠나 타향에서 살게 되는 경우가 많다.일복이 터져 바쁘게 살고 성공과 돈을 거머쥘 가능성이 높다.회사의 중역·임원이 되거나 사업가로 성공하는 이가 많다.\n";
		break;
	case 2:
		temp += "정사각형 얼굴 전(田)자형 : 정사각형 얼굴은 남성에게 많다.활동적이고 신뢰감을 주는 대장부형으로 무리의 리더가 된다.중년에 성공해 자기 기반을 확실히 다지며 부동산과 인연이 깊다.\n";
		break;
	case 3:
		temp += "직사각형 얼굴 동(同)자형 : 정사각형 얼굴보다 아래로 약간 긴 얼굴형이다.부모운이 있어 생활의 기반을 초년에 마련한다.평생 풍족하게 살며 장수할 운이 있다.대인관계가 좋지만 그로 인해 손해를 볼 수도 있다.\n";
		break;
	case 4:
		temp += "역삼각형 얼굴 V자형 : 갸름하고 세련되어 보이며 미인형으로 알려지면서 많이 선호하는 얼굴형 이지만, 중년 이후 운세가 급격히 나빠지고, 수명에 문제가 생기는 경우도 많다. 가정적으로 문제가 생길 가능성이 많은 얼굴형으로 변한다.\n";
		break;
	case 5:
		temp += "타원형 얼굴 달걀형 :온화하고 편안한 인상을 준다. 초년의 운은 좋지 않으나 말년으로 갈수록 운이 상승한다. 또한 자신을 내세우기를 좋아하며, 다른 사람들에게 인정받는 것을 그 누구보다 좋아한다.\n";
		break;
	}

	//눈썹 정보 추가하는 부분
	temp += "\n눈썹\n\n";
	switch (faceData[1]) {
	case 1:
		temp += "초승달 형 눈썹 : 예로부터 미인들이 가지는 초승달 눈썹, 청정하고 높게 빼난 눈썹으로 인정이 깊고 형제관계가 좋으며, 애정운이 따르는 눈썹 남자의 경우에는 성품이 신사다워 사람을 해치거나 막 대하지 못한다고 한다.\n";
		break;
	case 2:
		temp += "일자 형 눈썹 : 심성이 우직하고 신뢰가 있으며, 외롭고 강직한 사람의 눈썹\n";
		break;
	case 3:
		temp += "팔자 형 눈썹 : 부드럽고 젠틀한 사람으로 감정이입을 잘해 다른 사람의 문제도 나의 일처럼 함께 고민해줄 주 아는 사람.\n";
		break;
	case 4:
		temp += "칼 형 눈썹 : 모양이 칼같은 모양이고, 일자로 뻗어 있는 모습 성품이 귀하고 청렴하다.가난하더라도 못된짓을 안하고 정직하게 사는 사람이다.지모가 뛰어나고 강직해서 장군이나 재상에게서 많이 보이는 눈썹.\n";
		break;
	case 5:
		temp += "용 형 눈썹 : 활을 당긴 것처럼 구부정한 모습이다. 하는 일마다 잘되고, 평생 부귀영화를 누릴 팔자를 가진 사람으로 뛰어난 능력으로 세상에 널리 알려지게 될 눈썹.\n";
		break;
	case 6:
		temp += "수양버들 형 눈썹 : 음탕함을 가지고 다니는 사람.\n";
		break;
	}

	//눈 정보 추가하는 부분
	temp += "\n눈\n\n";
	switch (faceData[2]) {
	case 1:
		temp += "용의 눈 : 크고 귀하게 되는 상으로 높은 자리에 오를 상.\n";
		break;
	case 2:
		temp += "원앙의 눈 : 부부간에 정이 좋고 화순하다\n";
		break;
	case 3:
		temp += "도화안 : 부드럽고 젠틀한 사람으로 감정이입을 잘해 다른 사람의 문제도 나의 일처럼 함께 고민해줄 주 아는 사람.\n";
		break;
	case 4:
		temp += "삼백안 : 모양이 칼같은 모양이고, 일자로 뻗어 있는 모습 성품이 귀하고 청렴하다.가난하더라도 못된짓을 안하고 정직하게 사는 사람이다.지모가 뛰어나고 강직해서 장군이나 재상에게서 많이 보이는 눈썹.\n";
		break;
	case 5:
		temp += "사백안 : 활을 당긴 것처럼 구부정한 모습이다. 하는 일마다 잘되고, 평생 부귀영화를 누릴 팔자를 가진 사람으로 뛰어난 능력으로 세상에 널리 알려지게 될 눈썹.\n";
		break;
	case 6:
		temp += "수양버들 형 눈썹 : 음탕함을 가지고 다니는 사람.\n";
		break;
	}

	//미간 정보 추가하는 부분
	temp += "\n미간\n\n";
	switch (faceData[3]) {
	case 1:
		temp += "주름이 있는 미간 : 치밀한 계산력을 가지고 꼼꼼하고 까다로운 성격. 판단력이 좋고 분석이 빠르나 인정미가 적게 느껴진다. 의지가 강하고 줏대가 있으며 성격이 강직하지만 다소 막무가내의 성향을 보이기도 한다.\n";
		break;
	case 2:
		temp += "넓은 미간 : 개방적이고 사교성이 좋고 낙천적 성품을 가지고 있다. 어려운 일을 만나면 특유의 타고난 낙천성으로 사물이나 현상을 긍정적으로 바라보면서 꼬인 실타래를 풀어나가는 형\n";
		break;
	case 3:
		temp += "좁은 미간 : 미간이 좁은 사람은 소심한 편이어서 하찮은 일에도 신경질이 많은 성격이다. 또한 걱정거리를 늘 갖고 있거나 고민이 많은 성격인데 이것은 부정적인 사고방식을 가지고 있다는 뜻이다\n";
		break;
	}

	temp += "\n입\n\n";
	switch (faceData[4]) {
	case 1:
		temp += "아래입술이 두툼한 입술 : 착하고 성실한 성격의 소유자이다.성격이 급하고 여유가 없는 편이라 한템포 쉬어가는 것이 좋다.\n";
		break;
	case 2:
		temp += "윗입술이 두툼한 입술 : 애정이 깊고 적극적이다. 풍부한 감정의 소유자, 연애를 매우 잘하는 타입.\n";
		break;
	case 3:
		temp += "위아래 두께가 같은 입술 : 의지가 매우 강하고 사려깊은 성격이다. 그러나 자기 중심적이고 독립적으로 보이는 면이 있다.\n";
		break;
	case 4:
		temp += "입꼬리가 올라간 입술 : 긍정적이고 쾌활한 성격의 소유자. 대인관계가 좋다.\n";
		break;
	case 5:
		temp += "입꼬리가 내려간 입술 : 불만이 많고 소극적인 성격이 많다. 목표의식이 강해 목표를 뚜렷히 가지고 실천한다.\n";
		break;
	}

	::MessageBox(NULL, temp.c_str(),
		"MFC", MB_OK);
}


void CMFCTestDialog::OnBnClickedAnimal()
{
	int animal[5];		//1. 강아지 상 2. 고양이 상 3. 말 상 4. 개 상 5. 여우 상
	for (int i = 0; i < 5; i++) {
		animal[i] = 0;
	}

	//얼굴형태에 따른 초기화
	switch (faceData[0])
	{
	case 1:
		animal[0]++;
		animal[3]++;
		break;
	case 2:
		break;
	case 3:
		animal[2]++;
		break;
	case 4:
		animal[1]++;
		animal[4]++;
		break;
	case 5:
		animal[0]++;
		animal[1]++;
		animal[3]++;
		break;
	}

	//눈썹형태에 따른 초기화
	switch (faceData[1])
	{
	case 1:
		animal[0]++;
		animal[1]++;
		animal[4]++;
		break;
	case 2:
		animal[0]++;
		animal[2]++;
		animal[3]++;
		break;
	case 3:
		animal[2]++;
		break;
	case 4:
		animal[0]++;
		animal[3]++;
		break;
	case 5:
		animal[1]++;
		animal[2]++;
		animal[3]++;
		break;
	case 6:
		animal[1]++;
		animal[2]++;
		animal[4]++;
		break;
	}

	//눈형태에 따른 초기화
	switch (faceData[1])
	{
	case 1:
		animal[0]++;
		animal[1]++;
		animal[2]++;
		animal[3]++;
		break;
	case 2:
		animal[0]++;
		break;
	case 3:
		animal[2]++;
		break;
	case 4:
		animal[1]++;
		animal[3]++;
		animal[4]++;
		break;
	case 5:
		animal[4]++;
		break;
	}

	//입형태에 따른 초기화
	switch (faceData[1])
	{
	case 1:
		animal[2]++;
		break;
	case 2:
		animal[0]++;
		animal[1]++;
		animal[3]++;
		animal[4]++;
		break;
	case 3:
		animal[1]++;
		animal[4]++;
		break;
	case 4:
		animal[0]++;
		animal[1]++;
		animal[3]++;
		animal[4]++;
		break;
	case 5:
		animal[2]++;
		break;
	}
	int max = 0;
	int max_index = 0;
	for (int i = 0; i < 5; i++) {
		if (max < animal[i]) {
			max = animal[i];
			max_index = i;
		}
	}

	string temp = "당신은 ";

	switch (max_index) {
	case 0:
		temp += "강아지 상입니다.\n\n 강아지상​은 대부분 눈꼬리가 고양이상에 비해 살짝 쳐지면서 착해보이는 인상에 동글동글한 얼굴을 가진 사람들이 많다고 합니다. 대체로 귀엽고 순한 이미지로 대표적인 강아지상 연예인으로는,박보영, ​문근영, 송혜교, 한가인 등이 있습니다.\n";
		break;
	case 1:
		temp += "고양이 상입니다.\n\n 고양이상은 대부분 눈이 크면서 눈꼬리가 위로 올라가 있고 얼굴 라인이 갸름한 V라인 이라고 합니다. 앙큼하고 도발적이며 대표적인 고양이상 연예인은 이효리, 김희선, 한예슬, 한채영 등이 있습니다​.\n";
		break;
	case 2:
		temp += "말 상입니다.\n\n 얼굴 폭이 좁고 긴 사람들을 말상으로 분류한다. 얼굴의 어느 한 부분이 긴 경우가 많은데, 주로 코가 길거나 하관이 길다면 얼굴이 전체적으로 길어보인다. 말상은 동안이 거의 없고, 대체적으로 성숙한 느낌이 강하다. 대표적인 말상 연예인은 이문세, 최시원 등이 있습니다.\n";
		break;
	case 3:
		temp += "개 상입니다.\n\n 강아지 상과 비슷하게 귀여운 면이 있지만, 때로는 강하고 든든한 면이 부각되기도 합니다. 대체로 강한 눈매와 귀여움이 공존하는 얼굴입니다. 대표적인 개상 연예인으로는 고수, 권상우 등이 있습니다.\n";
		break;
	case 4:
		temp += "여우 상입니다.\n\n 높은 콧대와 시원한 눈매를 바탕으로 날카롭고 도도해보이지만 아름다운 이목구비가 특징입니다. 여우상은 차가운이미지를 가져서 쉽게 다가가기 어려워보이기도 합니다. 대표적인 여우상 연예인으로는	유인나, 박지윤, 서인국 등이 있습니다.\n";
		break;
	}

	::MessageBox(NULL, temp.c_str(),
		"MFC", MB_OK);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCTestDialog::OnBnClickedchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMFCTestDialog::set_faceData(int* facestyle) {
	faceData = new int[5];
	for (int i = 0; i < 5; i++) {
		faceData[i] = *(facestyle + i);
	}
}
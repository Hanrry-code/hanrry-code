#ifndef __ROBOTERROR_H__
#define __ROBOTERROR_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        ����궨��                                                         *
 *****************************************************************************/
#ifndef int8
#define int8 signed char
#endif
#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef U16
#define U16 unsigned short 
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef Boolean
#define Boolean unsigned short
#endif




#define public_function
#define private_function
#define public_variable

///////////////////////////////////////////////////////////////////// �������
// [[ ͨѶ����
#define ERR_COMM_LINK   	3000001	// LinkͨѶ����
#define ERR_COMM_NOMDT  	3000002	// ��MDT����
#define ERR_GRIPCOMM    	3000003	// ��צͨѶ����
#define ERR_GRIPDISABLE 	2000004	// ��צδʹ��
#define ERR_LINKAGEINIT 	3000005	// Linkage��ʼ������
#define ERR_SERIALCOMM  	3000006	// ����ͨѶ����
#define ERR_USERFRAMESET  	2000007	// �û�����ϵ�����쳣
#define ERR_COMM_DATA	  	3000008	// ͨѶ�����쳣
#define ERR_COMM_ALM        3000009 // �ŷ�����
#define ERR_COMM_DATA_TEST	  	3900008	// ͨѶ�����쳣
// ]]

// [[ �������
#define ERR_PROG_PARA   	2001000	// �����˶���������
#define ERR_PROG_POINT  	2001001	// �������������
#define ERR_PROG_PLIM   	2001002	// ����㴦�ڼ���
#define ERR_PROG_PSINGU 	2001003	// ����㴦������λ��
#define ERR_PROG_POUT   	2001004	// ����㳬�������ռ�
#define ERR_PROG_PINLIN 	2001005	// Բ�����㹲��
#define ERR_PROG_PCLOSE 	2001006	// Բ���������
#define ERR_PROG_PMIDERR    2001007 // Բ���м�����
#define ERR_PROG_TABLE_ZONE   2001010  //ת̨��תʹ�õ�����
// ]]

// [[ �滮����
#define ERR_PLAN_BUFF		3002000	// ����������
#define ERR_PLAN_NOENDLINE	2002001	// �޽�β��
#define ERR_PLAN_PLIM		2002002	// λ�ü���
#define ERR_PLAN_NOINV		2002003	// �����
#define ERR_PLAN_SPEED		2002004	// �Ӽ��ٹ滮����
#define ERR_PLAN_VELLIM		2002005	// �滮�ٶȳ���
#define ERR_PLAN_BUFF_EMPTY	3002006	// ��������
#define ERR_PLAN_NOMATRIX		2002007	// �޾���
#define ERR_PLAN_NOINVMATRIX		2002008	// �������
#define ERR_PLAN_LOSTCODE		2002018	// ָ��ID��ʧ
#define ERR_PLAN_PUTPRJ		2002019	// ·��������ָ��ID��ʧ
#define ERR_PLAN_GETPRJ		2002020	// �켣������ָ��ID��ʧ
#define ERR_PLAN_ENQELEM		2002021	// �岹���������ָ��ID��ʧ
#define ERR_PLAN_DEQELEM		2002022	// �岹����������ָ��ID��ʧ
#define ERR_PLAN_DEQELEMLOST		2002023	// �岹����������ָ���ж�ʧ
#define ERR_PLAN_LOSTLINE		2002024	// ָ���ж�ʧ
// ]]

// [[ �˶�����
#define ERR_EMGSTOP			2003000	// ����ֹͣ
#define ERR_CMODESTOP		2003001	// �˶�ģʽ�ı伱ͣ
#define ERR_USINGU			2003002	// J3����״̬
#define ERR_BSINGU			2003003	// J5����״̬
#define ERR_UNSINGU			1003004	// J3�ӽ�����λ��
#define ERR_BNSINGU			1003005	// J5�ӽ�����λ��
#define ERR_OWORKSPACE		2003006	// ���������ռ�
#define ERR_DATAEMPTY		2003007	// ���ݿ�Ѩ, λ��ͻ��
#define ERR_INTERPMODE		2003008	// �岹ģʽ����
#define ERR_OTC_CIA_APPRCH	2003009	// �����˼������������
#define ERR_JOINT_NOSYNC	2003010	// ���ת�Ǻ͹ؽ�ֵ����
// ]]

// [[ �ٶȼ���
#define ERR_SVLIM			2004000	// J1���ٶȳ���
#define ERR_LVLIM			2004001	// J2���ٶȳ���
#define ERR_UVLIM			2004002	// J3���ٶȳ���
#define ERR_RVLIM			2004003	// J4���ٶȳ���
#define ERR_BVLIM			2004004	// J5���ٶȳ���
#define ERR_TVLIM			2004005	// J6���ٶȳ���
// ]]

// [[ �ŷ�����
#define SV_SALM				2005000	// J1���ŷ�����
#define SV_LALM				2005001	// J2���ŷ�����
#define SV_UALM				2005002	// J3���ŷ�����
#define SV_RALM				2005003	// J4���ŷ�����
#define SV_BALM				2005004	// J5���ŷ�����
#define SV_TALM				2005005	// J6���ŷ�����
#define SV_NOZERO			2005006 // ��㶪ʧ
#define SV_DISABLE			2005007 // disable
// ]] 

// [[ ���ޱ���
#define OTS_SSLIMP   	 	2006001	// J1+����λ
#define OTS_LSLIMP			2006002	// J2+����λ
#define OTS_USLIMP			2006003	// J3+����λ
#define OTS_RSLIMP			2006004	// J4+����λ
#define OTS_BSLIMP			2006005	// J5+����λ
#define OTS_TSLIMP			2006006	// J6+����λ
#define OTS_T1SLIMP			2006007	// T1+����λ
#define OTS_T2SLIMP			2006008	// T2+����λ

#define OTS_SSLIMN			2006021	// J1-����λ
#define OTS_LSLIMN			2006022	// J2-����λ
#define OTS_USLIMN			2006023	// J3-����λ
#define OTS_RSLIMN			2006024	// J4-����λ
#define OTS_BSLIMN			2006025	// J5-����λ
#define OTS_TSLIMN			2006026	// J6-����λ
#define OTS_T1SLIMN			2006027	// T1-����λ
#define OTS_T2SLIMN			2006028	// T2-����λ


#define OTS_SNSLIMP 		1006001	// S+�ӽ�����, ����, ����ǰ����
#define OTS_LNSLIMP 		1006002	// L+�ӽ�����
#define OTS_UNSLIMP 		1006003	// U+�ӽ�����
#define OTS_RNSLIMP 		1006004	// R+�ӽ�����
#define OTS_BNSLIMP			1006005	// B+�ӽ�����
#define OTS_TNSLIMP 		1006006	// T+�ӽ�����
#define OTS_T1NSLIMP		1006007	// T1+�ӽ�����
#define OTS_T2NSLIMP 		1006008	// T2+�ӽ�����

#define OTS_SNSLIMN 		1006021	// S-�ӽ�����
#define OTS_LNSLIMN 		1006022	// L-�ӽ�����
#define OTS_UNSLIMN 		1006023	// U-�ӽ�����
#define OTS_RNSLIMN 		1006024	// R-�ӽ�����
#define OTS_BNSLIMN 		1006025	// B-�ӽ�����
#define OTS_TNSLIMN 		1006026	// T-�ӽ�����
#define OTS_T1NSLIMN 		1006027	// T1-�ӽ�����
#define OTS_T2NSLIMN 		1006028	// T2-�ӽ�����
// ]] ���ޱ���

// [[ ʾ�̴���
#define ERR_TEACH_COOR  	2007000	// ʾ������ϵ����
#define ERR_TEACH_COOR_DATA  	2007001	// ʾ������ϵ����
// ]]

// ����������
#define ERR_OTC_CIA_ENTER	2008000	// �����˽��������
#define ERR_OTC_CIA_DATA	2008001	// ���������������쳣

//����ʼ������
#define ERR_ARMInit			3009000	// ARM��ʼ������
#define ERR_ZERO_LOST		3009001 // ����������쳣

// IO����
#define ERR_IO_VALUE_OUT	2010001	// IO���ֵ����
#define ERR_IO_VALUE_IN		2010002	// IO����ֵ����
#define ERR_IO_TYPE			2010003	// IO�����ʹ���
#define ERR_IO_INDEX		2010004	// IO���Ŵ���
#define ERR_IO_WRITE		2010005	// IOд����

#ifdef __cplusplus
}
#endif
#endif

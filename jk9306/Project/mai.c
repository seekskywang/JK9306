Write421(0x42,0x11);

Write421(4,0);
Write421(5,0x01);//SaveData.div[1].bx[1]
Write421(6,0);//SaveData.div[1].bx[2]
Write421(7,0);//SaveData.div[1].bx[3]
//2
Write421(8,0);
Write421(9,0x01);//SaveData.div[2].bx[1]
Write421(10,0);//SaveData.div[2].bx[2]
Write421(11,0);//SaveData.div[2].bx[3]
//3
Write421(12,0);
Write421(13,0x01);//SaveData.div[3].bx[1]
Write421(14,0);//SaveData.div[3].bx[2]
Write421(15,0);//SaveData.div[3].bx[3]
//4
Write421(16,0);
Write421(17,0x01);//SaveData.div[4].bx[1]
Write421(18,0);////SaveData.div[4].bx[2]
Write421(19,0);//SaveData.div[4].bx[3]
//5
Write421(20,0);
Write421(21,0x01);//SaveData.div[5].bx[1]
Write421(22,0);//SaveData.div[5].bx[2]
Write421(23,0);//SaveData.div[5].bx[3]
//6
Write421(24,0);
Write421(25,0x01);//SaveData.div[6].bx[1]
Write421(26,0);//SaveData.div[6].bx[2]
Write421(27,0);//SaveData.div[6].bx[3]
//7
Write421(28,0);
Write421(29,0x01);//SaveData.div[7].bx[1]
Write421(30,0);//SaveData.div[7].bx[2]
Write421(31,0);//SaveData.div[7].bx[3]
//8
Write421(32,0);
Write421(33,0x01);//SaveData.div[8].bx[1]
Write421(34,0);//SaveData.div[8].bx[2]
Write421(35,0);//SaveData.div[8].bx[3]
//9
Write421(36,0);
Write421(37,0x01);//SaveData.div[9].bx[1]
Write421(38,0);//SaveData.div[9].bx[2]
Write421(39,0);//SaveData.div[9].bx[3]


do
{
key=rd421(0x41);
}
while(key!=0x11);
Write421(0x40,0x11);

Write421(0x2b,4);
Write421(0x2c,0);
Write421(0x2d,0);
Write421(0x2e,0);
Write421(0x2f,0);


tst_rang=0x17;
w42h=0x12;



while(1)
    {

Write421(0x2a,0x80);//start
	Write421(0x28,tst_rang);//4rang0x17
	Write421(0x29,0x1);//speed
Write421(0x42,w42h);//trig

	do
	{
	Delay(15);
		R_flg=rd421(0x34);//Read test flag 
}
while((R_flg&0x80)==0);


Write421(0x2a,0x00);//wr 2ah=0

	do
	{	Delay(15);
		R_flg=rd421(0x34);//Read test flag 

	}
while((R_flg&0x80)==1);//=0 go on

	Write421(0x2a,0x00);//wr 2ah=0

		test_r=(uint32_t)Disp_R();
	
	tst_rang=Disp_Test_Date.Main_RBuff[1];//>>4;
tst_rang>>=4;

km=Disp_Test_Date.Main_RBuff[2];
	if(km==0xdd)
	{tst_rang++;
		if(tst_rang>7)tst_rang=8;
		
	}
	if(km==0xcc)
		{tst_rang--;
		if(tst_rang<2)tst_rang=1;
			
	}
	//	tst_rang|=0x80;
	
	tst_rang=0x04;
	do
{
	Delay(15);
	R_flg=rd421(0x41);

}
while(R_flg!=w42h);//

w42h++;

}


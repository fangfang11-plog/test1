//*****************************************************************************************                                                                                                                                                  
//���ܣ�ָ��λ����LCDд��ָ���ַ�
//*****************************************************************************************
void write_lcd(uchar x,uchar y,char *cha)
{
  uint place,i=0;
  uchar length,c1,c2,j,k;
  
        for(length=0;cha[length]!=0;length++);
  do
  {
    c1=cha[i];                                                                                                                                                              //ȡ�ַ�����ASCII��
    c2=cha[i+1];
    place=x*30+y;
    if(c1<=128)                                                                                                                                                        //С��128Ϊ�ַ�������128Ϊ����
    {
                        for(k=0;k<16;++k)                                                                                                                             //�ַ�����Ϊ16*8
      {
        write_data(place&0xff);                                                                                                   //д���ַ��λ
        write_data(place/256);                                                                                                    //д���ַ��λ
        write_com(0x24);                                                                                                          //��ַ����
        write_com(0xb0);                                                                                                          //���������Զ�д
        write_data(ASC_MSK[(c1-0x20)*16+k]);                                                         //���磺0��ASCII��Ϊ0x30,��ASC_MSK�е�λ��Ϊ0x10*16 ---16�ֽ���������д��LCD
        write_com(0xb2);                                                                                                                  //�Զ���λ
        place=place+30;
      }
      if(y>28)                                                                                                                                            //y>28ʱ����Ҫ����
      {
                                x=x+16;
                                y=0;
                        }
      else                                                                                                                                                //���򣬲����У�����д��һ���ַ�
      {
                                y++;
                        }
      i++;
    }
    else                                                                                                                                                   //c1����128Ϊ����
    {
      for(j=0;j<sizeof(GB_16)/sizeof(GB_16[0]);j++)                          //�ҵ�����
      {
        if(c1==GB_16[j].Index[0]&&c2==GB_16[j].Index[1])
                                {
                                        break;                                                                                                                                    //�����ҵ������� 
                                }
      }
      if(j<sizeof(GB_16)/sizeof(GB_16[0]))                                                           //����������������
      {
        for(k=0;k<16;k++)                                                                                                                     //�ַ�����Ϊ16*8
        {
          write_data(place&0xff);                                                                                           //д���ַ��λ
          write_data(place/256);                                                                                            //д���ַ��λ
          write_com(0x24);                                                                                                  //��ַ����
          write_com(0xb0);                                                                                                  //���������Զ�д
          write_data(GB_16[j].Msk[k*2]);
                                        write_data(GB_16[j].Msk[k*2+1]);                                                                 //16*16,ÿ��2�ֽ�
          write_com(0xb2);                                                                                             //�Զ���λ
          place=place+30;                                                                                              //��һ��
        }
      }
      else                                                                                                                                                             //û�ҵ���Ӧ������Ϳ��
      {
        for(k=0;k<16;k++)                                                                                                                     //�ַ�����Ϊ16*8
        {
                                        write_data(place&0xff);                                                                                           //д���ַ��λ
          write_data(place/256);                                                                                            //д���ַ��λ
          write_com(0x24);                                                                                                  //��ַ����
          write_com(0xb0);                                                                                                  //��ַ����
          write_data(0xff);
                                        write_data(0xff); 
          write_com(0xb2);                                                                                             //�Զ���λ
          place=place+30;                                                                                              //��һ��
        }
      }
      if(y>27)                                                                                                                                                              //����
      {
                                x+=16;y=0;
                        }
      else                                                                                                                                                                  //���û��У�����һ����
      {
                                y+=2;
                        }
      i+=2;
    } 
  }
  while(i<length);
}
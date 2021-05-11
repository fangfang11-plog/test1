//*****************************************************************************************                                                                                                                                                  
//功能：指定位置向LCD写入指定字符
//*****************************************************************************************
void write_lcd(uchar x,uchar y,char *cha)
{
  uint place,i=0;
  uchar length,c1,c2,j,k;
  
        for(length=0;cha[length]!=0;length++);
  do
  {
    c1=cha[i];                                                                                                                                                              //取字符串的ASCII码
    c2=cha[i+1];
    place=x*30+y;
    if(c1<=128)                                                                                                                                                        //小于128为字符，大于128为汉字
    {
                        for(k=0;k<16;++k)                                                                                                                             //字符设置为16*8
      {
        write_data(place&0xff);                                                                                                   //写入地址高位
        write_data(place/256);                                                                                                    //写入地址低位
        write_com(0x24);                                                                                                          //地址设置
        write_com(0xb0);                                                                                                          //设置数据自动写
        write_data(ASC_MSK[(c1-0x20)*16+k]);                                                         //例如：0的ASCII码为0x30,在ASC_MSK中的位置为0x10*16 ---16字节字码依次写入LCD
        write_com(0xb2);                                                                                                                  //自动复位
        place=place+30;
      }
      if(y>28)                                                                                                                                            //y>28时候需要换行
      {
                                x=x+16;
                                y=0;
                        }
      else                                                                                                                                                //否则，不换行，继续写下一个字符
      {
                                y++;
                        }
      i++;
    }
    else                                                                                                                                                   //c1大于128为汉字
    {
      for(j=0;j<sizeof(GB_16)/sizeof(GB_16[0]);j++)                          //找到汉字
      {
        if(c1==GB_16[j].Index[0]&&c2==GB_16[j].Index[1])
                                {
                                        break;                                                                                                                                    //汉字找到则跳出 
                                }
      }
      if(j<sizeof(GB_16)/sizeof(GB_16[0]))                                                           //如果汉字在子码表内
      {
        for(k=0;k<16;k++)                                                                                                                     //字符设置为16*8
        {
          write_data(place&0xff);                                                                                           //写入地址高位
          write_data(place/256);                                                                                            //写入地址低位
          write_com(0x24);                                                                                                  //地址设置
          write_com(0xb0);                                                                                                  //设置数据自动写
          write_data(GB_16[j].Msk[k*2]);
                                        write_data(GB_16[j].Msk[k*2+1]);                                                                 //16*16,每行2字节
          write_com(0xb2);                                                                                             //自动复位
          place=place+30;                                                                                              //下一行
        }
      }
      else                                                                                                                                                             //没找到对应汉字则涂黑
      {
        for(k=0;k<16;k++)                                                                                                                     //字符设置为16*8
        {
                                        write_data(place&0xff);                                                                                           //写入地址高位
          write_data(place/256);                                                                                            //写入地址低位
          write_com(0x24);                                                                                                  //地址设置
          write_com(0xb0);                                                                                                  //地址设置
          write_data(0xff);
                                        write_data(0xff); 
          write_com(0xb2);                                                                                             //自动复位
          place=place+30;                                                                                              //下一行
        }
      }
      if(y>27)                                                                                                                                                              //换行
      {
                                x+=16;y=0;
                        }
      else                                                                                                                                                                  //不用换行，则下一个字
      {
                                y+=2;
                        }
      i+=2;
    } 
  }
  while(i<length);
}
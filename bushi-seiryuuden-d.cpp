#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

struct pos_t
{
    uint16_t in, out;
};

using namespace std;

int main(int argc, char **argv)
{
    const unsigned int BUFFER_SIZE=0x2000;
    const unsigned int POINTER_SIZE=0x400;
    const unsigned int REF_SIZE=0x400;

    uint8_t in_buf[BUFFER_SIZE]={0};
    uint8_t out_buf[BUFFER_SIZE]={0};
    
    uint8_t p_buf[BUFFER_SIZE]={0};
    uint8_t r_buf[REF_SIZE]={0};
    
    //uint16_t dist[16]={0x1,0x20,0x21,0x84,0x40,0x41,0x80,0x81,0x82,0x2,0x43,0x100,0x101,0x102,0x4,0x200};
    uint16_t dist[16]={0x2,0x40,0x42,0x108,0x80,0x82,0x100,0x102,0x104,0x4,0x86,0x200,0x202,0x204,0x8,0x400};

    uint32_t in_pos = 0;
    uint32_t out_pos = 0;
    uint32_t p_pos = 0;
    uint32_t r_pos = 0;
    
    uint32_t in_off = 0x1BA5A4;
    uint32_t p_off = 0x1BA1A4;    
    uint32_t r_off = 0x1BB4EE;
    
     // char *off;
   // uint8_t header[2];
  //  uint16_t comp_size;
    //rle_t rle;

    FILE *in_file;
    FILE *out_file;
      
    const char* in_name = "Bushi Seiryuuden - Futari no Yuusha (J).smc";
    const char* out_name = "Bushi Seiryuuden - Futari no Yuusha (J)_decomp.bin";
  
    //const char* in_name = argv[1];
    //cout << "agv[1]=" << argv[1] << endl;
    //const char* out_name = argv[2];
    //cout << "agv[2]=" << argv[2] << endl;

    in_file = fopen(in_name, "rb");
    out_file = fopen(out_name, "wb");
    
     //in_file = fopen(argv[1], "rb");
    //    in_file = fopen(in_name, "rb");
    //    if (in_file==NULL)
    //    {
    //        fputs ("Input file error",stderr);
    //        exit (1);
   //     }

        //out_file = fopen(argv[2], "wb");
    //    out_file = fopen(out_name, "wb");
  //      if (out_file==NULL)
   //     {
  //          fputs ("Output file error",stderr);
  //          exit (1);
  //      }
        
  //      off = argv[3];
//if (off==NULL){fputs ("Offset error",stderr); exit (1);}

//sscanf (off, "%x", &offset);
    
    //fseek  (in_file,offset,SEEK_SET);
  //  fread(header,sizeof(uint8_t),sizeof(header),in_file);

    //comp_size=(header[1]<<8)|header[0];

    //cout << hex << "Size of data to be decompressed: " << (int)comp_size;
    //cout << hex << "\nOffset: " << (int)offset;
    
    
    fseek(in_file,p_off,SEEK_SET);
    fread(p_buf,sizeof(uint8_t),POINTER_SIZE,in_file);
    
    fseek(in_file,r_off,SEEK_SET);
    fread(r_buf,sizeof(uint8_t),POINTER_SIZE,in_file);
    
    fseek(in_file,in_off,SEEK_SET);
    fread(in_buf,sizeof(uint8_t),BUFFER_SIZE,in_file);
    
    fclose(in_file);
    
    uint16_t ref=0;
    uint16_t r=0;
    //uint16_t d=0;
    uint8_t cnt=0;
    uint8_t r1=0;
    uint8_t r2=0;
    
            
        uint16_t c=0;
        uint8_t c1=0;
        uint8_t c2=0;
        uint8_t e=0;
        uint32_t off=0;
    
    
    
    //while (out_pos<BUFFER_SIZE)
    while (p_pos<1024)
    {


        cout << hex << "\nP.pos.=[" << setw(4) << (int) p_pos << "]";
        cout << hex << " In.pos.=[" << setw(4) << (int) in_pos << "]";
        cout << hex << " Out.pos.=[" << setw(4) << (int) out_pos << "]";

        c1=p_buf[p_pos++];
        c2=p_buf[p_pos++];
        c=c1|(c2<<8);
        
        cout << hex << " C=[" << setw(4) << (int) c << "]" << endl;
        
        for (int i=0;i<8;i++)
        {
            cout << hex << " I=[" << setw(4) << (int) i << "]";            
            e=c>>14;
            e=e&0x3;
            cout << hex << " E=[" << setw(4) << (int) e << "]";            
            switch (e)
        {

        case (0x00):
        
            cout << hex << "\tCASE: 0x00";          
			cout << hex << " [" << setw(4) << (int) in_buf[in_pos] << "]";
            out_buf[out_pos++]=in_buf[in_pos++];
            cout << hex << " [" << setw(4) << (int) in_buf[in_pos] << "]" << endl;
            out_buf[out_pos++]=in_buf[in_pos++];            
            break;
            
            
        case (0x01):

            cout << hex << "\tCASE: 0x01" << endl;
            break;                
            

        case (0x02):

            cout << hex << "\tCASE: 0x02";            
            if (cnt==0)
            {
			cnt=4;
			r1=r_buf[r_pos++];
			cout << hex << " r1 = [" << setw(4) << (int) r1 << "]";			
            r2=r_buf[r_pos++];
            cout << hex << " r2 = [" << setw(4) << (int) r2 << "]";
            ref=(r1|(r2<<8))&0xffff;
            cout << hex << " ref = [" << setw(4) << (int) ref << "]";
            r=((ref&0xf000)>>12)&0x000f;
            cout << hex << " r = [" << setw(4) << (int) r << "]";
            cout << hex << " d = [" << setw(4) << (int) dist[r] << "]";
            off = out_pos-dist[r];
            cout << hex << " off = [" << setw(4) << (int) off << "]";
            cnt--;
            //ref=(ref<<4)&0xffff;             
		    }
		    
		    else
		    {
				ref=(ref<<4)&0xffff;
				cout << hex << " ref = [" << setw(4) << (int) ref << "]";
				r=((ref&0xf000)>>12)&0x000f;
				 cout << hex << " r = [" << setw(4) << (int) r << "]";
				cout << hex << " d = [" << setw(4) << (int) dist[r] << "]";
			off = out_pos-dist[r];
			cout << hex << " off = [" << setw(4) << (int) off << "]";
            cnt--;  
            //ref=(ref<<4)&0xffff;           
			
			}
            
            //off = out_pos-1;
            cout << hex << " [" << setw(4) << (int) out_buf[off] << "]";
            out_buf[out_pos++]=out_buf[off++];				
            cout << hex << " [" << setw(4) << (int) out_buf[off] << "]" << endl;
            out_buf[out_pos++]=out_buf[off++];				
            
            break;
            
            
        case (0x03):
        
			cout << hex << "\tCASE: 0x03";
			 cout << hex << " r = [" << setw(4) << (int) r << "]";
cout << hex << " d = [" << setw(4) << (int) dist[r] << "]";
			off = out_pos-dist[r];
			cout << hex << " off = [" << setw(4) << (int) off << "]";
            //cnt--; 


            //off = out_pos-2;
            cout << hex << " [" << setw(4) << (int) out_buf[off] << "]";
            out_buf[out_pos++]=out_buf[off++];				
            cout << hex << " [" << setw(4) << (int) out_buf[off] << "]" << endl;
            out_buf[out_pos++]=out_buf[off++];				
            
            break;           
        }
        
        cout << "SHIFT [C]";
        c=(c<<2)&0xffff;    
            
            
        }
        
        

        
    }
cout << hex << "\nDecompressed data size: " << (int)out_pos;
    fwrite(out_buf,sizeof(uint8_t),out_pos,out_file);
    fclose(out_file);
    return 0;
};

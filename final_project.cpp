#include <bits/stdc++.h>
//#include <fstream.h>
#define pi 3.141592653589793238
#define Re 6378.1

using namespace std;

ifstream cab_list("cab_driver_list.json");
ofstream nearer_cab("output_file.json");


void output_fun(double, double, double, double, long int, char*);
double distance_on_earth(double, double, double, double);

char lat_str[1000], long_str[1000], name_str[1000], id_str[1000];

string line;
int j=0;
//long int id;

void parser_fun(double lat1, double long1)
{
    if(cab_list.is_open())
    {
        while(getline(cab_list, line))
        {
            int quote=0, x=0, y=0, z=0, coloumn=0,w=0;
            for(int i=0;i<line.size();i++)
            {
                if(line[i]=='"')
                quote++;
                
                if(line[i]==':')
                coloumn=coloumn+1;
                
            if(quote==3)
            {
                i++;
                while(line[i]!='"')
                {
                    lat_str[x]=line[i];
                    i++;
                    x++;
                }
                lat_str[x]='\0';
                i--;
            }
                
                if(quote==9)
                {
                    i++;
                    while(line[i]!='"')
                    {
                        name_str[y]=line[i];
                        i++;
                        y++;
                    }
                    name_str[y]='\0';
                    i--;
                }
                
                if(quote==13)
                {
                    i++;
                    while(line[i]!='"')
                    {
                        long_str[z]=line[i];
                        i++;
                        z++;
                    }
                    long_str[z]='\0';
                    i--;
                } 
                
                if(coloumn==2)
                {
                    coloumn=coloumn+1;
                    i=i+2;
                    while(line[i]!=',')
                    {
                       id_str[w]=line[i];
                       i++;
                        w++;
                    }
                    
                    id_str[w]='\0';
                    i--;
                }
            }
            
            double lat2=atof(lat_str);
            double long2=atof(long_str);
            long int id=atol(id_str);
            // char *name=name_str;
            
            //cout<<lat2<<name_str<<long2<<" "<<lat1<<" "<<long1;
             
            output_fun(lat1, long1, lat2, long2, id, name_str);
    
       }
        
    }
    cab_list.close();
   // nearer_cab.close();
}

void output_fun(double lat1, double long1, double lat2, double long2, long int id, char* name)
{
    double distance= distance_on_earth(lat1, long1, lat2, long2);
    
   if(distance <= 50.00)
    {
       nearer_cab << "{\"user_id\": "<< id <<", \"name\": " << name << "}" << endl;
    }
    
    //cout<<distance<<endl;
}



double distance_on_earth(double lat1, double long1, double lat2, double long2)
{
    double latr_1= (lat1*pi)/180;
    double latr_2= (lat2*pi)/180;
    double longr_1= (long1*pi)/180;
    double longr_2= (long2*pi)/180;
    
    double a_x=cos(latr_1)*cos(longr_1);
    double a_y=cos(latr_1)*sin(longr_1);
    double a_z=sin(latr_1);
    
    double b_x=cos(latr_2)*cos(longr_2);
    double b_y=cos(latr_2)*sin(longr_2);
    double b_z=sin(latr_2);
    
    double ab=sqrt(pow((a_x - b_x),2)+pow((a_y - b_y),2)+pow((a_z - b_z),2));
    
    double ang_at_centre=2*asin(ab/2);
    
    return ang_at_centre*Re;
    //return (ang_at_centre*180)/pi;
    
}





int main()
{
    double lat1, long1;
    //cordinates cord_persn;
    cout<<"enter the latitude of person in degree"<<endl;
    cin>>lat1;
    cout<<"enter the longitude of person in degree"<<endl;
    cin>>long1;
    
    parser_fun(lat1, long1);
    

    return 0;
}


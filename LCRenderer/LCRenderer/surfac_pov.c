//#include <stdio.h>
//#include <math.h>
//#define TOTAL 24332
//#define ELLIP 13500
//#define SURFAC 10832
//#define CONVERT 57.2957795
//
//void main() {
//
//	int 		number, total, type, ellip_tot, water_tot;
//
//	double	ellip_x[ELLIP], ellip_y[ELLIP], ellip_z[ELLIP];
//	double	ellip_ux[ELLIP], ellip_uy[ELLIP], ellip_uz[ELLIP];
//	double	ellip_rz[ELLIP], ellip_ry[ELLIP];
//	double	major_radius = 2.2;
//
//	double	surfac_x[SURFAC], surfac_y[SURFAC], surfac_z[SURFAC];
//	int i,j,k,n;	
//	double trash, theta, phi;
//	FILE *pFile;
//   FILE *traj;
//
//
//	/* READ IN FROM TRAJ FILE*/
//
//	traj = fopen("traj.inp","r");
////	traj = fopen("initial.inp","r");
//
//	for(i=0;i<total;i++) {
//	fscanf(traj,"%d", &number);
//	fscanf(traj,"%d", &type);
//	number = number - 1;
//	
//		if(type == 1) {
//			
//			fscanf(traj,"%lf", &ellip_x[number]);
//			fscanf(traj,"%lf", &ellip_y[number]);
//			fscanf(traj,"%lf", &ellip_z[number]);
//			
//			fscanf(traj,"%lf", &ellip_ux[number]);
//			fscanf(traj,"%lf", &ellip_uy[number]);
//			fscanf(traj,"%lf", &ellip_uz[number]);
//			fscanf(traj,"%lf", &trash);
//
//		}		
//
//
//		if(type == 2) {
//			
//			fscanf(traj,"%lf", &surfac_x[number-ELLIP]);
//         fscanf(traj,"%lf", &surfac_y[number-ELLIP]);
//         fscanf(traj,"%lf", &surfac_z[number-ELLIP]);
//
//         fscanf(traj,"%lf", &trash);
//         fscanf(traj,"%lf", &trash);
//         fscanf(traj,"%lf", &trash);
//         fscanf(traj,"%lf", &trash);
//		}
//	}
//
//	fclose(traj);
//
//	
//	for(i=0;i<ELLIP;i++) {
//		ellip_rz[i] = atan2( ellip_uy[i] , ellip_ux[i])*CONVERT;
//		ellip_ry[i] = atan2( ellip_uz[i] , sqrt( (ellip_ux[i]*ellip_ux[i]+ellip_uy[i]*ellip_uy[i] )))*CONVERT;
//	}
//
//
// 	pFile = fopen("drop.pov","w");
//
//
//	fprintf(pFile,"#include \"colors.inc\" \n");
//	fprintf(pFile,"#include \"finish.inc\" \n\n");
//	fprintf(pFile,"background { color White } \n");
//	fprintf(pFile,"light_source { <0,0,-60> color White }\n");
//
//	fprintf(pFile,"camera\n{ location <0,0,-70> \n look_at <0,0,0> } \n\n");
//
//
////    LIMITS FOR VISION 
//
//	for(k=0;k<SURFAC;k++) {
//		if(surfac_z[k] < 0) continue;
//		fprintf(pFile,"sphere{ <%lf,%lf,%lf>, 0.5 pigment{ color Red} }\n", surfac_x[k], surfac_y[k], surfac_z[k]);
//	}
//	
//
//	for(n=0;n<ELLIP;n++) { 
//		if(ellip_z[n] < 0) continue;
//		double x = fabs(ellip_ux[n]);
//		double y = fabs(ellip_uy[n]);
//		double z = fabs(ellip_uz[n]);
//
//		fprintf(pFile, \
//		" sphere{ <0,0,0>, 1 scale <%lf, 0.5, 0.5> rotate< 0, %lf, %lf > translate<%lf,%lf,%lf>  pigment{ color rgb<%lf,%lf,%lf> } finish{ specular 0.2 roughness 0.05  }  } \n"  \ 
//	 	, major_radius,ellip_ry[n],ellip_rz[n],ellip_x[n],ellip_y[n],ellip_z[n],x,y,z);
//		}	
//
//
//	fclose(pFile);
//
//	pFile = fopen("distance.out","w");
//
//	for(i=0;i<SURFAC;i++) {
//		double distance = sqrt(surfac_x[i]*surfac_x[i]+surfac_y[i]*surfac_y[i]+surfac_z[i]*surfac_z[i]);
//		fprintf(pFile,"%lf \n",distance);
//	}
//
//
//	fclose(pFile);
//
//}

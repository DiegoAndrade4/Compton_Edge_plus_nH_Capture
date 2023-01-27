#!/bin/bash




#Include proxtrackdist cut 
#R&D data 
./blipana BlipAna_20221206_RadonData_FullFilter.root OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_fulldet.root OutputFilesNoEshift 22  DataRadonFullFilter_0percEshift_fulldet 0.0  data fulldet

./blipana BlipAna_20221206_RadonData_FullFilter.root OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root OutputFilesNoEshift 22  DataRadonFullFilter_0percEshift_G10 0.0  data G10

./blipana BlipAna_20221206_RadonData_FullFilter.root OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root OutputFilesNoEshift 22  DataRadonFullFilter_0percEshift_NonG10 0.0  data NonG10


#Run 3 data
./blipana BlipAna_20221206_Run3_Unbiased.root OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_fulldet.root OutputFilesNoEshift 22  DataRun3Unbiased_0percEshift_fulldet 0.0  data fulldet

./blipana BlipAna_20221206_Run3_Unbiased.root OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_G10.root OutputFilesNoEshift 22  DataRun3Unbiased_0percEshift_G10 0.0  data G10

./blipana BlipAna_20221206_Run3_Unbiased.root OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_NonG10.root OutputFilesNoEshift 22  DataRun3Unbiased_0percEshift_NonG10 0.0  data NonG10



#MC-Overlay
./blipana BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay.root OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_fulldet.root OutputFilesNoEshift 22  OverlayMCgammas2pt6_0percEshift_fulldet 0.0  mcoverlay fulldet

./blipana BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay.root OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_G10.root OutputFilesNoEshift 22  OverlayMCgammas2pt6_0percEshift_G10 0.0  mcoverlay G10

./blipana BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay.root OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_NonG10.root OutputFilesNoEshift 22  OverlayMCgammas2pt6_0percEshift_NonG10 0.0  mcoverlay NonG10



root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_fulldet.root\",\"OutputFilesNoEshift\" ,\"Overlay_gammas_2pt6MeV_fulldet_EshiftPercent_0\",  0,  1.0, 1.0, 1 )

root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_G10.root\",\"OutputFilesNoEshift\" ,\"Overlay_gammas_2pt6MeV_G10_EshiftPercent_0\",  0,  1.0, 1.0, 1 )

root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_NonG10.root\",\"OutputFilesNoEshift\" ,\"Overlay_gammas_2pt6MeV_NonG10_EshiftPercent_0\",  0,  1.0, 1.0, 1 )



#No proxtrackdist cut
#FullMC
./blipana_fullmc BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc.root OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc_fulldet.root OutputFilesNoEshift 22  FullMCgammas2pt6_0percEshift_fulldet 0.0  fullmc fulldet

./blipana_fullmc BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc.root OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc_G10.root OutputFilesNoEshift 22  FullMCgammas2pt6_0percEshift_G10 0.0  fullmc G10

./blipana_fullmc BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc.root OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc_NonG10.root OutputFilesNoEshift 22  FullMCgammas2pt6_0percEshift_NonG10 0.0  fullmc NonG10



root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc_fulldet.root\",\"OutputFilesNoEshift\" ,\"FullMC_gammas_2pt6MeV_fulldet_EshiftPercent_0\",  0,  1.0, 1.0, 0 )

root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc_G10.root\",\"OutputFilesNoEshift\" ,\"FullMC_gammas_2pt6MeV_G10_EshiftPercent_0\",  0,  1.0, 1.0, 0 )

root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc_NonG10.root\",\"OutputFilesNoEshift\" ,\"FullMC_gammas_2pt6MeV_NonG10_EshiftPercent_0\",  0,  1.0, 1.0, 0 )




#Testing
#./blipana BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay.root OutputFilesNoEshiftTest/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_fulldet.root OutputFilesNoEshiftTest 22  OverlayMCgammas2pt6_0percEshift_fulldet 0.0  mcoverlay fulldet

#./blipana BlipAna_20221206_RadonData_FullFilter.root OutputFilesNoEshiftTest/output_BlipAna_20221206_RadonData_FullFilter_G10.root OutputFilesNoEshiftTest 22  DataRadonFullFilter_0percEshift_G10 0.0  data G10

#./blipana BlipAna_20221206_RadonData_FullFilter.root OutputFilesNoEshiftTest/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root OutputFilesNoEshiftTest 22  DataRadonFullFilter_0percEshift_NonG10 0.0  data NonG10
#

#root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshiftTest/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshiftTest/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_overlay_G10.root\",\"OutputFilesNoEshift\" ,\"Overlay_gammas_2pt6MeV_G10_EshiftPercent_0\",  0,  1.0, 1.0, 1 )


#root -b -q Plot_MC_Data_gammas_shift_withChi2.C+(\"OutputFilesNoEshiftTest/output_BlipAna_20221206_Run3_Unbiased_G10.root\", \"OutputFilesNoEshiftTest/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\",  \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_G10.root\", \"OutputFilesNoEshift/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\",   \"OutputFilesNoEshift/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6MeV_G10_5struts_100k_fullmc.root\",\"OutputFilesNoEshift\" ,\"Overlay_gammas_2pt6MeV_G10_EshiftPercent_0\",  0,  1.0, 1.0, 1 )



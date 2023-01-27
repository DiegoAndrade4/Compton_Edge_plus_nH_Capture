#!/bin/bash


# 1 eV neutrons

./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay.root OutputFiles_OOTB/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_G10.root OutputFiles_OOTB 2112  G10_OverlayMC_neutrons1eV_0percEshift 0.0  mcoverlay G10


./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay.root OutputFiles_OOTB/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_NonG10.root OutputFiles_OOTB 2112  NonG0_OverlayMC_neutrons1eV_0percEshift 0.0  mcoverlay NonG10


./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay.root OutputFiles_OOTB/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_fulldet.root OutputFiles_OOTB 2112  FullDet_OverlayMC_neutrons1eV_0percEshift 0.0  mcoverlay fulldet




# 2.6 MeV gammas

./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD.root OutputFiles_OOTB/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_G10.root OutputFiles_OOTB 22  G10_OverlayMC_gammas2pt6_0percEshift 0.0  mcoverlay G10

./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD.root OutputFiles_OOTB/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_NonG10.root OutputFiles_OOTB 22  NonG10_OverlayMC_gammas2pt6_0percEshift 0.0  mcoverlay NonG10

./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD.root OutputFiles_OOTB/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_fulldet.root OutputFiles_OOTB 22  FullDet_OverlayMC_gammas2pt6_0percEshift 0.0  mcoverlay fulldet 




# Run 6 data R&D

./blipana ../BlipAnaFiles/BlipAna_20221206_RadonData_FullFilter.root OutputFiles_OOTB/output_BlipAna_20221206_RadonData_FullFilter_G10.root OutputFiles_OOTB 0  G10_DataRun6_0percEshift 0.0  data G10

./blipana ../BlipAnaFiles/BlipAna_20221206_RadonData_FullFilter.root OutputFiles_OOTB/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root OutputFiles_OOTB 0  NonG10_DataRun6_0percEshift 0.0  data NonG10

./blipana ../BlipAnaFiles/BlipAna_20221206_RadonData_FullFilter.root OutputFiles_OOTB/output_BlipAna_20221206_RadonData_FullFilter_fulldet.root OutputFiles_OOTB 0  FullDet_DataRun6_0percEshift 0.0  data fulldet




#Run 3 data

./blipana ../BlipAnaFiles/BlipAna_20221206_Run3_Unbiased.root OutputFiles_OOTB/output_BlipAna_20221206_Run3_Unbiased_G10.root OutputFiles_OOTB 0  G10_DataRun3_0percEshift 0.0  data G10

./blipana ../BlipAnaFiles/BlipAna_20221206_Run3_Unbiased.root OutputFiles_OOTB/output_BlipAna_20221206_Run3_Unbiased_NonG10.root OutputFiles_OOTB 0  NonG10_DataRun3_0percEshift 0.0  data NonG10

./blipana ../BlipAnaFiles/BlipAna_20221206_Run3_Unbiased.root OutputFiles_OOTB/output_BlipAna_20221206_Run3_Unbiased_fulldet.root OutputFiles_OOTB 0  FullDet_DataRun3_0percEshift 0.0  data fulldet

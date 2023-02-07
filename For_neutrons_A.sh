#!/bin/bash



for percEshift in $(seq -2.5 0.01 3.0)
do
  echo "Sequence value $percEshift "


#./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD.root OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_G10_$percEshift.root OutputFiles_Shifted_fs 22  G10_OverlayMC_gammas2pt6_percEshift_$percEshift $percEshift  mcoverlay G10

#./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD.root OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_NonG10_$percEshift.root OutputFiles_Shifted_fs 22  NonG10_OverlayMC_gammas2pt6_percEshift_$percEshift $percEshift  mcoverlay NonG10

#./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay.root OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_G10_$percEshift.root OutputFiles_Shifted_fs 2112  G10_OverlayMC_neutrons1eV_0percEshift_$percEshift $percEshift  mcoverlay G10


#./blipana ../BlipAnaFiles/BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay.root OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_NonG10_$percEshift.root OutputFiles_Shifted_fs 2112  NonG0_OverlayMC_neutrons1eV_percEshift_$percEshift $percEshift  mcoverlay NonG10



for SNFrun3 in $(seq 0.10 0.01 0.40)
  do

  echo "Sequence value EShift: $percEshift , SNFrun3: $SNFrun3 ,  SNFrun6: -1 "
# IsMCOverlay set to true,  Addneutros set to false, doPlot set to false, Fit region 2 to 2.6
 root -b -q Plot_Eshift_Chi2CalcFit.C+(\"OutputFiles_OOTB_COM/output_BlipAna_20221206_Run3_Unbiased_G10.root\" , \"OutputFiles_OOTB_COM/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\", \"OutputFiles_OOTB_COM/output_BlipAna_20221206_RadonData_FullFilter_G10.root\" , \"OutputFiles_OOTB_COM/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\" , \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_G10_$percEshift.root\", \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_NonG10_$percEshift.root\", \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_G10_$percEshift.root\", \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_NonG10_$percEshift.root\", \"OutDirChi2_2p0To2p6_fs_neutrons\",  \"plots\", $percEshift,  $SNFrun3, -1.0, true , true , false, 2.0, 2.6 )


  done



  for SNFrun6 in $(seq 0.10 0.01 0.40)
  do

  echo "Sequence value EShift: $percEshift , SNFrun3: -1 ,  SNFrun6: $SNFrun6 "


 root -b -q Plot_Eshift_Chi2CalcFit.C+(\"OutputFiles_OOTB_COM/output_BlipAna_20221206_Run3_Unbiased_G10.root\" , \"OutputFiles_OOTB_COM/output_BlipAna_20221206_Run3_Unbiased_NonG10.root\", \"OutputFiles_OOTB_COM/output_BlipAna_20221206_RadonData_FullFilter_G10.root\" , \"OutputFiles_OOTB_COM/output_BlipAna_20221206_RadonData_FullFilter_NonG10.root\" , \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_G10_$percEshift.root\", \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_gammas_2pt6_G10_5struts_overlay_CAD_NonG10_$percEshift.root\", \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_G10_$percEshift.root\", \"OutputFiles_Shifted_fs/output_BlipAna_v08_00_00_63_lowROIthreshold_neutrons_1eV_G10_5struts_overlay_NonG10_$percEshift.root\", \"OutDirChi2_2p0To2p6_fs_neutrons\",  \"plots\", $percEshift, -1.0, $SNFrun6, true , true , false, 2.0, 2.6 )






    done



done



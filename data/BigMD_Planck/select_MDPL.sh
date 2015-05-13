for i in 0 1 2 3 4 5 
do
   awk < /srv/cosmdata/multidark/BigMD_3840_Planck1/BDM/CatshortW.0080.0$i.DAT '{if($8>5.0E11 && $15==0)print $0}' > BigMD_BDMW_snap_80_Mvir_5E11_0$i.dat
done

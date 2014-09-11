PATH_IN=/srv/cosmdata/multidark/SMD_3840_Planck1/BDM/
PATH_OUT=../data/
PREFIX=MassiveMain

FILE_IN=CatshortV.0088.00.DAT
$(PATH_OUT)MassiveMain$(FILE_IN) : $(PATH_IN)$(FILE_IN)
	awk < $(PATH_IN)$(FILE_IN) '{if(($$8>4.0E+11 )&& ($$15==0)) print $$0}' > $(PATH_OUT)MassiveMain$(FILE_IN)


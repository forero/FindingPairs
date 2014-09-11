PATH_IN=/srv/cosmdata/multidark/SMD_3840_Planck1/BDM/
PATH_OUT=../data/
PREFIX=MassiveMain

FILE_IN_A=CatshortV.0088.00.DAT
FILE_IN_B=CatshortV.0088.01.DAT
FILE_IN=CatshortV.0088.DAT
$(PATH_OUT)MassiveMain$(FILE_IN) : $(PATH_IN)$(FILE_IN_A) $(PATH_IN)$(FILE_IN_B)
	awk < $(PATH_IN)$(FILE_IN_A) '{if(($$8>4.0E+11 )&& ($$15==0)) print $$1,$$2,$$3,$$4,$$5,$$6,$$7,$$8,$$9,$$10,$$11,$$12,$$13,$$14}'> \
$(PATH_OUT)MassiveMain$(FILE_IN_A)
	awk < $(PATH_IN)$(FILE_IN_B) '{if(($$8>4.0E+11 )&& ($$15==0)) print $$1,$$2,$$3,$$4,$$5,$$6,$$7,$$8,$$9,$$10,$$11,$$12,$$13,$$14}'> \
$(PATH_OUT)MassiveMain$(FILE_IN_B)
	cat $(PATH_OUT)MassiveMain$(FILE_IN_A) $(PATH_OUT)MassiveMain$(FILE_IN_B) > $(PATH_OUT)MassiveMain$(FILE_IN)

clean:
	rm -f $(PATH_OUT)MassiveMain$(FILE_IN)

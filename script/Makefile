PATH_IN=/srv/cosmdata/multidark/MD_3840_Planck1/BDM/
PATH_OUT=../data/MD_3840_Planck1/
EXEC_PATH=../src/
SOURCE_PATH=../src/
PREFIX=MassiveMain

FILE_IN_A=CatshortW.0088.00.DAT
FILE_IN_B=CatshortW.0088.01.DAT
FILE_IN_C=CatshortW.0088.02.DAT
FILE_IN_D=CatshortW.0088.03.DAT
FILE_IN_E=CatshortW.0088.04.DAT
FILE_IN=CatshortW.0088.DAT

all: $(PATH_OUT)properties_memberA.dat $(PATH_OUT)properties_memberB.dat 


sample: 
	awk < $(PATH_IN)$(FILE_IN_A) '{if(($$8>5.0E+11 )&& ($$15==0)) print $$1,$$2,$$3,$$4,$$5,$$6,$$7,$$8,$$9,$$10,$$11,$$12,$$13,$$14}'> \
$(PATH_OUT)MassiveMain$(FILE_IN_A)
	awk < $(PATH_IN)$(FILE_IN_B) '{if(($$8>5.0E+11 )&& ($$15==0)) print $$1,$$2,$$3,$$4,$$5,$$6,$$7,$$8,$$9,$$10,$$11,$$12,$$13,$$14}'> \
$(PATH_OUT)MassiveMain$(FILE_IN_B)
	awk < $(PATH_IN)$(FILE_IN_C) '{if(($$8>5.0E+11 )&& ($$15==0)) print $$1,$$2,$$3,$$4,$$5,$$6,$$7,$$8,$$9,$$10,$$11,$$12,$$13,$$14}'> \
$(PATH_OUT)MassiveMain$(FILE_IN_C)
	awk < $(PATH_IN)$(FILE_IN_D) '{if(($$8>5.0E+11 )&& ($$15==0)) print $$1,$$2,$$3,$$4,$$5,$$6,$$7,$$8,$$9,$$10,$$11,$$12,$$13,$$14}'> \
$(PATH_OUT)MassiveMain$(FILE_IN_D)
	awk < $(PATH_IN)$(FILE_IN_E) '{if(($$8>5.0E+11 )&& ($$15==0)) print $$1,$$2,$$3,$$4,$$5,$$6,$$7,$$8,$$9,$$10,$$11,$$12,$$13,$$14}'> \
$(PATH_OUT)MassiveMain$(FILE_IN_E)
	cat $(PATH_OUT)MassiveMain*W.0088.0*.DAT  > $(PATH_OUT)MassiveMain$(FILE_IN)

$(PATH_OUT)properties_memberA.dat: $(PATH_OUT)PairIndex$(FILE_IN) $(EXEC_PATH)dump_pair_properties.py 
	python $(EXEC_PATH)dump_pair_properties.py $(PATH_OUT)PairIndex$(FILE_IN) $(PATH_OUT)MassiveMain$(FILE_IN) $(PATH_OUT)

$(PATH_OUT)PairIndex$(FILE_IN) : $(PATH_OUT)AllPairIndex$(FILE_IN) $(EXEC_PATH)quick_pair.x
	$(EXEC_PATH)./quick_pair.x $(PATH_OUT)AllPairIndex$(FILE_IN) > $(PATH_OUT)PairIndex$(FILE_IN)

$(PATH_OUT)AllPairIndex$(FILE_IN) : $(PATH_OUT)MassiveMain$(FILE_IN) $(EXEC_PATH)correlate.x
	$(EXEC_PATH)./correlate.x $(PATH_OUT)MassiveMain$(FILE_IN) $(PATH_OUT)MassiveMain$(FILE_IN) $(PATH_OUT)AllPairIndex$(FILE_IN) 40 1000.0 0.0 

$(EXEC_PATH)correlate.x: $(EXEC_PATH)correlate_cl.c $(EXEC_PATH)struct.h
	cc $(EXEC_PATH)correlate_cl.c -lm -o $(EXEC_PATH)correlate.x

$(EXEC_PATH)quick_pair.x: $(EXEC_PATH)quick_pair.c 
	cc $(EXEC_PATH)quick_pair.c -lm -o $(EXEC_PATH)quick_pair.x



clean_deep:
	rm -f $(PATH_OUT)MassiveMain$(FILE_IN)
	rm -f $(PATH_OUT)AllPairIndex$(FILE_IN) 
	rm -f $(PATH_OUT)PairIndex$(FILE_IN) 
	rm -f $(EXEC_PATH)correlate.x
	rm -f $(EXEC_PATH)quick_pair.x

clean:
	rm -f $(PATH_OUT)AllPairIndex$(FILE_IN) 
	rm -f $(PATH_OUT)PairIndex$(FILE_IN) 
	rm -f $(PATH_OUT)properties_memberA.dat $(PATH_OUT)properties_memberB.dat 
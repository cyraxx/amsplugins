#
# Platform/Configuration independent makefile for building 64bit access library
#

SrcDir := .
OutputDir := ./build
InstallDir := /opt/adobe/ams/modules/access/
ObjDir := $(OutputDir)
AccessInclude := $(SrcDir)/../include/

AccessLib := ${OutputDir}/libconnect.so

AccessSrcs := 	${SrcDir}/adaptor.cpp

AccessObjs := $(patsubst %.cpp,$(ObjDir)/%.o,$(notdir $(AccessSrcs)))

SHARED := -shared
ACCESS_CC = $(CC)
ACCESS_CXX := $(CXX)
ACCESS_LDFLAGS := $(LDFLAGS) $(DBGFLAGS)
ACCESS_CXXFLAGS := $(CXXFLAGS) $(DBGFLAGS) -m64 -fPIC -DTINCAN -DTINCAN_SERVER -DUNIX -D_REENTRANT ${USE_STLPORT} -DTC_UNICODE

ACCESS_CXXFLAGS := $(ACCESS_CXXFLAGS) \
		-I$(SrcDir)  \
		-I$(AccessInclude)

-include $(AccessObjs:.o=.d)

$(OutputDir)/%.o: $(SrcDir)/%.cpp
	mkdir -p $(ObjDir)
	$(ACCESS_CXX) $(ACCESS_CXXFLAGS) $< -c -o $@

.PHONY: access clean

access: $(AccessLib)

install: access
	mkdir -p $(InstallDir)
	cp $(AccessLib) $(InstallDir)

clean:
	-rm -rf $(AccessLib) $(ObjDir)

$(AccessLib): $(AccessObjs)
	$(ACCESS_CXX) $(SHARED) -o $(AccessLib) $(AccessObjs)

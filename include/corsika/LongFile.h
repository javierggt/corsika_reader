/**
 \file
 Reader for Corsika generated shower file
 
 \author Javier Gonzalez
 \version $Id$
 \date 14 Jul 2016
 */

#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <corsika/LongProfile.h>

namespace corsika
{
    
    
    /**
     \class CorsikaLongFile CorsikaLongFile.h "corsika/CorsikaLongFile.h"
     
     \brief Read data from .long files generated by CORSIKA
     
     \author Javier Gonzalez
     \date 14 Jul 2016
     \ingroup corsika
     */
    struct LongFile
    {
        LongFile(std::string filename, double zenith=0.);
        ~LongFile()
        {
            Close();
        }
        
        void Close()
        {
            if (fLongDataFile->is_open()) {fLongDataFile->close();}
        }
        
        LongProfile GetProfile(size_t event);
        
        size_t size() const { return event_count; }
        float Dx() const { return fDx; }
        bool HasParticleProfile() const { return fPartProfiles.size(); }
        bool HasEnergyDeposit() const { return fdEdXProfiles.size(); }
        bool IsSlantDepth() const { return fIsSlantDepthProfile; }
        
    private:
        void Scan();
        LongProfile FetchProfile(size_t i);
        
        std::string fFilename;
        
        float fCosZenith;
        bool fIsSlantDepthProfile;
        size_t event_count;
        float fDx;
        size_t fNBinsParticles;
        int fNBinsEnergyDeposit;
        
        boost::shared_ptr<std::ifstream> fLongDataFile;
        std::vector<std::streampos> fPartProfiles;
        std::vector<std::streampos> fdEdXProfiles;
        
    };    
}
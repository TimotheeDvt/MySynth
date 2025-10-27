/****************************************************************
libscala-file, (C) 2020 Mark Conway Wirt
See LICENSE for licensing terms (MIT)
****************************************************************/
#pragma once

#include <fstream>
#include <cmath>
#include <vector>
#include <string>

#define KBM_NON_ENTRY -1

namespace scala {

    class degree {
    private:
        double ratio;

    public:
        degree(int n, int d) {
            ratio = static_cast<double>(n) / static_cast<double>(d);
        }

        explicit degree(double cents) {
            ratio = pow(pow(2, 1.0 / 12.0), cents / 100.0);
        }

        double getRatio() const {
            return ratio;
        }
    };

    class scale {
    private:

    public:
        std::vector<degree> degrees;
        std::string name;
        std::string description;
        scale() {
            degrees.push_back(degree(0.0));
        }

        ~scale() {
            degrees.clear();
        }

        scale(const scale& other) {
            degrees = other.degrees;
            name = other.name;
            description = other.description;
        }

        scale& operator=(const scale& other) {
            if (this != &other) {
                degrees = other.degrees;
                name = other.name;
                description = other.description;
            }
            return *this;
        }

        void addDegree(const degree& d) {
            degrees.push_back(d);
        }

        double getRatio(size_t i) const {
            return degrees[i].getRatio();
        }

        size_t getScaleLength() const {
            return degrees.size();
        }

        std::string getName() const {
            return name;
        }

        void setName(const std::string& _name) {
            name = _name;
        }

        void setDescription(const std::string& _description) {
            description = _description;
        }

        std::string getDescription() const {
            return description;
        }
    };

    class KBM {
    private:

    public:
        double referenceFrequency;
        int mapSize;
        int firstNote;
        int lastNote;
        int middleNote;
        int referenceNote;
        int octaveDegree;
        std::vector<int> mapping;
        KBM() : referenceFrequency(0.0), mapSize(0), firstNote(0), lastNote(0),
                middleNote(0), referenceNote(0), octaveDegree(0) {}

        ~KBM() {
            mapping.clear();
        }

        KBM(const KBM& other) {
            mapping = other.mapping;
            mapSize = other.mapSize;
            firstNote = other.firstNote;
            lastNote = other.lastNote;
            middleNote = other.middleNote;
            referenceNote = other.referenceNote;
            referenceFrequency = other.referenceFrequency;
            octaveDegree = other.octaveDegree;
        }

        KBM& operator=(const KBM& other) {
            if (this != &other) {
                mapping = other.mapping;
                mapSize = other.mapSize;
                firstNote = other.firstNote;
                lastNote = other.lastNote;
                middleNote = other.middleNote;
                referenceNote = other.referenceNote;
                referenceFrequency = other.referenceFrequency;
                octaveDegree = other.octaveDegree;
            }
            return *this;
        }

        void addMapping(int n) {
            mapping.push_back(n);
        }

        // Getters
        double getReferenceFrequency() const { return referenceFrequency; }
        int getMapSize() const { return mapSize; }
        int getFirstNote() const { return firstNote; }
        int getLastNote() const { return lastNote; }
        int getMiddleNote() const { return middleNote; }
        int getReferenceNote() const { return referenceNote; }
        int getOctaveDegree() const { return octaveDegree; }
        const std::vector<int>& getMapping() const { return mapping; }

        // Setters
        void setReferenceFrequency(double f) { referenceFrequency = f; }
        void setMapSize(int s) { mapSize = s; }
        void setFirstNote(int n) { firstNote = n; }
        void setLastNote(int n) { lastNote = n; }
        void setMiddleNote(int n) { middleNote = n; }
        void setReferenceNote(int n) { referenceNote = n; }
        void setOctaveDegree(int n) { octaveDegree = n; }
    };

    scale read_scl(std::ifstream& input_file);
    KBM read_kbm(std::ifstream& input_file);
}

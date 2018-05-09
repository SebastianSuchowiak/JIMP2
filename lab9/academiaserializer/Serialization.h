//
// Created by sebastian on 08.05.18.
//

#ifndef JIMP_EXERCISES_SERIALIZATION_H
#define JIMP_EXERCISES_SERIALIZATION_H

#include <string>
#include <vector>
#include <ostream>
#include <memory>

namespace academia {

    class Serializer;

    class Serializable {

    public:
        virtual void Serialize(Serializer *serializer) const = 0;
    };


    class Serializer {

    public:

        explicit Serializer(std::ostream *out) : m_out{out}{};

        virtual void IntegerField(const std::string &field_name, int value) = 0;
        virtual void DoubleField(const std::string &field_name, double value) = 0;
        virtual void StringField(const std::string &field_name, const std::string &value) = 0;
        virtual void BooleanField(const std::string &field_name, bool value) = 0;
        virtual void SerializableField(const std::string &field_name, const academia::Serializable &value) = 0;
        virtual void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) = 0;
        virtual void Header(const std::string &object_name) = 0;
        virtual void Footer(const std::string &object_name) = 0;

    public:

        std::ostream *m_out;
    };


    class XmlSerializer : public Serializer {
    public:

        explicit XmlSerializer(std::ostream *out) : Serializer(out){};

        void IntegerField(const std::string &field_name, int value) override;

        void DoubleField(const std::string &field_name, double value) override;

        void StringField(const std::string &field_name, const std::string &value) override;

        void BooleanField(const std::string &field_name, bool value) override;

        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;

        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &values) override;

        void Header(const std::string &object_name) override;

        void Footer(const std::string &object_name) override;

    private:

        std::string XmlFormat(std::string name, std::string value) const;

    };


    class JsonSerializer : public Serializer {

    public:

        explicit JsonSerializer(std::ostream *out) : Serializer(out){}

        void IntegerField(const std::string &field_name, int value) override;

        void DoubleField(const std::string &field_name, double value) override;

        void StringField(const std::string &field_name, const std::string &value) override;

        void BooleanField(const std::string &field_name, bool value) override;

        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;

        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;

        void Header(const std::string &object_name) override;

        void Footer(const std::string &object_name) override;

    private:

        std::string JsonFormat(const std::string &name, const std::string &value);
        std::string JsonFormat(const std::string &name, int value);
        std::string JsonFormat(const std::string &name, double value);

    private:

        bool m_first_elem = true;
    };


    class Room : public Serializable {

    public:

        enum class Type {
            COMPUTER_LAB,
            LECTURE_HALL,
            CLASSROOM
        };

    public:
        
        Room(int id, const std::string &name, Room::Type type) :
                m_id{id},
                m_name{name},
                m_type{type}{};

        void Serialize(Serializer *serializer) const override;


    private:

        std::string TypeToString(Room::Type type) const;

    public:
        
        int m_id;
        std::string m_name;
        Room::Type m_type;
    };


    class Building : public Serializable {

    public:

        Building(int id, const std::string &name,
                 const std::initializer_list<Room> &rooms) :
                m_id{id},
                m_name{name},
                m_rooms{rooms}{};

        void Serialize(Serializer *serializer) const override;

    private:

        std::vector<std::reference_wrapper<const Serializable>> getWrappedRooms() const;

    private:

        int m_id;
        std::string m_name;
        std::vector<Room> m_rooms;
    };

}


#endif //JIMP_EXERCISES_SERIALIZATION_H

//
// Created by sebastian on 08.05.18.
//

#include <sstream>
#include "Serialization.h"

void academia::Room::Serialize(academia::Serializer *serializer) const {
    serializer->Header("room");
    serializer->IntegerField("id", m_id);
    serializer->StringField("name", m_name);
    serializer->StringField("type", TypeToString(m_type));
    serializer->Footer("room");
}

std::string academia::Room::TypeToString(academia::Room::Type type) const {
    switch(type) {
        case Type::COMPUTER_LAB:
            return "COMPUTER_LAB";
        case Type::LECTURE_HALL:
            return "LECTURE_HALL";
        case Type::CLASSROOM:
            return "CLASSROOM";
    }
}

void academia::Building::Serialize(academia::Serializer *serializer) const {
    serializer->Header("building");
    serializer->IntegerField("id", m_id);
    serializer->StringField("name", m_name);
    serializer->ArrayField("rooms", getWrappedRooms());
    serializer->Footer("building");
}

std::vector<std::reference_wrapper<const academia::Serializable>> academia::Building::getWrappedRooms() const {

    std::vector<std::reference_wrapper<const Serializable>> wrapped_rooms{};

    for (const Serializable &room: m_rooms){
        wrapped_rooms.emplace_back(room);
    }

    return wrapped_rooms;
}

void academia::XmlSerializer::IntegerField(const std::string &field_name, int value) {
    *m_out << XmlFormat(field_name, std::to_string(value));
}

void academia::XmlSerializer::DoubleField(const std::string &field_name, double value) {
    *m_out << XmlFormat(field_name, std::to_string(value));
}

void academia::XmlSerializer::StringField(const std::string &field_name, const std::string &value) {
    *m_out << XmlFormat(field_name, value);
}

void academia::XmlSerializer::BooleanField(const std::string &field_name, bool value) {
    *m_out << XmlFormat(field_name, std::to_string(value));
}

void academia::XmlSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value) {

    XmlSerializer temp_serializer = XmlSerializer{m_out};

    value.Serialize(&temp_serializer);
}

void academia::XmlSerializer::ArrayField(const std::string &field_name,
                                         const std::vector<std::reference_wrapper<const Serializable>> &values) {

    XmlSerializer temp_serializer = XmlSerializer{m_out};

    temp_serializer.Header(field_name);

    for (const Serializable &value: values) {
        value.Serialize(&temp_serializer);
    }

    temp_serializer.Footer(field_name);
}

void academia::XmlSerializer::Header(const std::string &object_name) {
    *m_out << "<" << object_name << ">";
}

void academia::XmlSerializer::Footer(const std::string &object_name) {
    *m_out << "<\\" << object_name << ">";
}

std::string academia::XmlSerializer::XmlFormat(const std::string name, const std::string value) const {
    return "<" + name + ">" + value + "<\\" + name + ">";
}


void academia::JsonSerializer::IntegerField(const std::string &field_name, int value) {
    *m_out << JsonFormat(field_name, value);
}

void academia::JsonSerializer::DoubleField(const std::string &field_name, double value) {
    *m_out << JsonFormat(field_name, value);
}

void academia::JsonSerializer::StringField(const std::string &field_name, const std::string &value) {
    *m_out << JsonFormat(field_name, value);
}

void academia::JsonSerializer::BooleanField(const std::string &field_name, bool value) {
    *m_out << JsonFormat(field_name, std::to_string(value));
}

void academia::JsonSerializer::SerializableField(const std::string &field_name, const Serializable &value) {
    JsonSerializer temp_serializer = JsonSerializer{m_out};

    value.Serialize(&temp_serializer);
}

void academia::JsonSerializer::ArrayField(const std::string &field_name,
                                          const std::vector<std::reference_wrapper<const Serializable>> &values) {

    JsonSerializer temp_serializer = JsonSerializer{m_out};
    int i = 0;

    if (m_first_elem)  {
        *m_out << "\"" << field_name << "\": [";
        m_first_elem = false;
    } else {
        *m_out << ", \"" << field_name << "\": [";
    }

    for (const Serializable &value: values) {
        value.Serialize(&temp_serializer);
        temp_serializer.m_first_elem = true;
        i++;
        if (i != values.size()) {
            *m_out << ", ";
        }
    }

    *m_out << "]";
}

void academia::JsonSerializer::Header(const std::string &object_name) {
    *m_out << "{";
}

void academia::JsonSerializer::Footer(const std::string &object_name) {
    *m_out << "}";
}

std::string academia::JsonSerializer::JsonFormat(const std::string &name, const std::string &value) {
    if(m_first_elem) {
        m_first_elem = false;
        return "\"" + name + "\": " + "\"" + value + "\"";
    }
    return ", \"" + name + "\": " + "\"" + value + "\"";
}

std::string academia::JsonSerializer::JsonFormat(const std::string &name, int value) {
    if(m_first_elem) {
        m_first_elem = false;
        return "\"" + name + "\": " + std::to_string(value);
    }
    return ", \"" + name + "\": " + std::to_string(value);
}

std::string academia::JsonSerializer::JsonFormat(const std::string &name, double value) {
    if(m_first_elem) {
        m_first_elem = false;
        return "\"" + name + "\": " + std::to_string(value);
    }
    return ", \"" + name + "\": " + std::to_string(value);
}

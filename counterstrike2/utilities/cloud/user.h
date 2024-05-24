#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <mutex>
#include "../nlohmann/json.hpp"
#include "../xorstr.h"

struct ConfigSettingsT;
class c_flatbuffers;

enum EProcessingType {
	Auth,
	Avatar,
	GetConfigs,
	Load,
	Save,
	Rename,
	Delete,
	Create,
	Parse,
	GetOnline,
	DEV
};

struct ProcessingRecord {
	std::string share;
	std::string name;
	nlohmann::json json;
	bool changed;

	ProcessingRecord() {}
	ProcessingRecord(std::string index_, bool changed) : share(index_), changed(changed) {}
	ProcessingRecord(std::string index_, std::string name_, bool changed) : share(index_), name(name_), changed(changed) {}
	ProcessingRecord(nlohmann::json js) : json(js), changed(true), share() {}

	void ResetRecord() {
		share.clear();
		changed = false;
		name.clear();
		json.clear();
	}
};

class CConfig
{
public:
	std::string name;
	std::string owner;
	std::string user;
	std::string share;
	bool available_share;
	std::string created;
	std::string updated;
	std::vector<std::uint8_t> data_; // is used for GetMutableRoot / GetRoot with class Config
	bool is_deleted;
};

class Online_ {
public:
	std::string username;
	std::vector<std::uint8_t> avatar;
};

class CUser {
public:
	void Processing(const EProcessingType type, const ProcessingRecord processing_record = ProcessingRecord());
	std::unordered_map<std::string, CConfig>& GetConfigs() {
		return configs_;
	}
	std::vector<Online_>& GetOnline() {
		return onlines_;
	}

	int GetAvatar(std::string username) {
		if (textures_.find(username) == textures_.end()) {
			textures_[username] = -1;
		}

		return textures_[username];
	}

	std::string GetUsername() {
		username_ = "nicesrc";

		return username_;
	}

	void SetUsername(const std::string username) {
		username_ = username;
	}

	std::unordered_map<std::string, double>& GetConfig() {
		return config_map_;
	}

	double IsActive(std::string var, std::string bind_var = "", int index = -1);
private:
	void Auth(ProcessingRecord processing_record_);
	void GetConfigList(ProcessingRecord processing_record_);
	void Load(ProcessingRecord processing_record_);
	void Save(ProcessingRecord processing_record_);
	void Rename(ProcessingRecord processing_record_);
	void Delete(ProcessingRecord processing_record_);
	void Create(ProcessingRecord processing_record_);
	void Parse(ProcessingRecord processing_record_);
	void Avatar(ProcessingRecord processing_record_);
	void GetOnline(ProcessingRecord processing_record_);
protected:
	std::uint64_t Hash(std::string str) {
		return std::hash<std::string>()(str);
	}
public:
	std::string username_ = "admin";
	std::string prefix_;
	std::string id_;
	std::uint64_t subtime_;
	std::unordered_map<std::string, CConfig> configs_;
	std::vector<Online_> onlines_;
	std::vector < std::uint8_t> avatar;
	std::unordered_map<std::string, int> textures_;
	std::unordered_map<std::string, double> config_map_;
	std::shared_ptr<ConfigSettingsT> config_;
	std::mutex mutex_;
	bool m_should_processing;
};

inline auto g_user = std::make_unique<CUser>();
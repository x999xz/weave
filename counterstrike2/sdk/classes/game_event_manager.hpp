#pragma once

class i_game_event_listener;

class game_event_manager
{
public:
	virtual ~game_event_manager() = 0;
	virtual int load_events_from_file(const char* filename) = 0;
	virtual void reset() = 0;
	virtual bool add_listeners(i_game_event_listener* Listener, const char* m_sName, bool m_bServerSide) = 0;
};
#pragma once

#include <lsp/protocol.h>
#include <lsp/InputHandler.h>
#include <json/value.h>

#include <functional>
#include <optional>
#include <ostream>
#include <unordered_map>
#include <variant>

namespace lsp {

/// Solidity Language Server, managing one LSP client.
class Server
{
public:
	using Id = protocol::Id;

	Server(std::ostream& _client, std::ostream& _logger);
	virtual ~Server() = default;

	void handleMessage(std::string const& _message);
	void handleMessage(Json::Value _message);

	// Client-to-Server messages
	virtual void operator()(protocol::CancelRequest const&) = 0;
	virtual void operator()(protocol::InitializeRequest const&) = 0;
	virtual void operator()(protocol::InitializedNotification const&) {};
	virtual void operator()(protocol::DidOpenTextDocumentParams const&) {}
	virtual void operator()(protocol::DidChangeTextDocumentParams const&) {}
	virtual void operator()(protocol::DidCloseTextDocumentParams const&) {}

protected:
	void sendReply(lsp::protocol::CancelRequest const& _message);
	void sendReply(Json::Value const& _response, std::optional<Id> _requestId = std::nullopt);

	std::ostream& logger() noexcept { return m_logger; }
	std::ostream& client() noexcept { return m_client; }

private:
	std::ostream& m_client;
	std::ostream& m_logger;
	InputHandler m_inputHandler;
};

} // namespace solidity

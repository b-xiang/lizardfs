#pragma once

#include "config.h"

#include "common/chunk_type.h"
#include "common/exception.h"
#include "common/mfsstrerr.h"
#include "common/network_address.h"

LIZARDFS_CREATE_EXCEPTION_CLASS(ReadException, Exception);
LIZARDFS_CREATE_EXCEPTION_CLASS(RecoverableReadException, ReadException);
LIZARDFS_CREATE_EXCEPTION_CLASS(UnrecoverableReadException, ReadException);
LIZARDFS_CREATE_EXCEPTION_CLASS(NoValidCopiesReadException, RecoverableReadException);

class ChunkCrcException : public RecoverableReadException {
public:
	ChunkCrcException(const std::string& message, const NetworkAddress& server,
			const ChunkType& chunkType)
			: RecoverableReadException(message + " (server " + server.toString() + ")"),
			  server_(server), chunkType_(chunkType) {
	}

	~ChunkCrcException() throw() {}
	const NetworkAddress& server() const throw() { return server_; }
	const ChunkType& chunkType() const throw() { return chunkType_; }

private:
	NetworkAddress server_;
	ChunkType chunkType_;
};
/*
 * MIT License
 *
 * Copyright (c) 2026 Popa Adrian Marius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FBCPP_DATABASE_MANAGER_H
#define FBCPP_DATABASE_MANAGER_H

#include "ServiceManager.h"
#include <cstdint>
#include <optional>
#include <string>


///
/// fb-cpp namespace.
///
namespace fbcpp
{
	///
	/// Represents options used to configure database properties through the service manager.
	///
	class DatabaseManagerOptions final
	{
	public:
		///
		/// Returns the database path to be configured.
		///
		const std::string& getDatabase() const
		{
			return database;
		}

		///
		/// Sets the database path to be configured.
		///
		DatabaseManagerOptions& setDatabase(const std::string& value)
		{
			database = value;
			return *this;
		}

		///
		/// Returns the replica mode.
		///
		const std::optional<ReplicaMode>& getReplicaMode() const
		{
			return replicaMode;
		}

		///
		/// Sets the replica mode.
		///
		DatabaseManagerOptions& setReplicaMode(ReplicaMode value)
		{
			replicaMode = value;
			return *this;
		}

	private:
		std::string database;
		std::optional<ReplicaMode> replicaMode;
	};

	///
	/// Represents options used to run a database maintenance operation through the service manager.
	///
	class MaintenanceOptions final
	{
	public:
		///
		/// Returns the database path to be maintained.
		///
		const std::string& getDatabase() const
		{
			return database;
		}

		///
		/// Sets the database path to be maintained.
		///
		MaintenanceOptions& setDatabase(const std::string& value)
		{
			database = value;
			return *this;
		}

		///
		/// Returns the verbose output callback.
		///
		const ServiceManager::VerboseOutput& getVerboseOutput() const
		{
			return verboseOutput;
		}

		///
		/// Sets the verbose output callback.
		///
		MaintenanceOptions& setVerboseOutput(ServiceManager::VerboseOutput value)
		{
			verboseOutput = std::move(value);
			return *this;
		}

		///
		/// Returns the requested number of parallel workers.
		///
		const std::optional<std::uint32_t>& getParallelWorkers() const
		{
			return parallelWorkers;
		}

		///
		/// Sets the requested number of parallel workers.
		///
		MaintenanceOptions& setParallelWorkers(std::uint32_t value)
		{
			parallelWorkers = value;
			return *this;
		}

		///
		/// Returns whether database sweep is enabled.
		///
		bool getSweep() const
		{
			return sweep;
		}

		///
		/// Sets whether database sweep is enabled.
		///
		MaintenanceOptions& setSweep(bool value)
		{
			sweep = value;
			return *this;
		}

		///
		/// Returns whether database validation is enabled.
		///
		bool getValidate() const
		{
			return validate;
		}

		///
		/// Sets whether database validation is enabled.
		///
		MaintenanceOptions& setValidate(bool value)
		{
			validate = value;
			return *this;
		}

		///
		/// Returns whether database mending is enabled.
		///
		bool getMend() const
		{
			return mend;
		}

		///
		/// Sets whether database mending is enabled.
		///
		MaintenanceOptions& setMend(bool value)
		{
			mend = value;
			return *this;
		}

		///
		/// Returns whether checksum verification is ignored.
		///
		bool getIgnoreChecksum() const
		{
			return ignoreChecksum;
		}

		///
		/// Sets whether checksum verification is ignored.
		///
		MaintenanceOptions& setIgnoreChecksum(bool value)
		{
			ignoreChecksum = value;
			return *this;
		}

		///
		/// Returns whether killing database shadows is enabled.
		///
		bool getKillShadows() const
		{
			return killShadows;
		}

		///
		/// Sets whether killing database shadows is enabled.
		///
		MaintenanceOptions& setKillShadows(bool value)
		{
			killShadows = value;
			return *this;
		}

		///
		/// Returns whether full validation is enabled.
		///
		bool getFull() const
		{
			return full;
		}

		///
		/// Sets whether full validation is enabled.
		///
		MaintenanceOptions& setFull(bool value)
		{
			full = value;
			return *this;
		}

		///
		/// Returns whether checking only metadata/structure is enabled.
		///
		bool getCheckDb() const
		{
			return checkDb;
		}

		///
		/// Sets whether checking only metadata/structure is enabled.
		///
		MaintenanceOptions& setCheckDb(bool value)
		{
			checkDb = value;
			return *this;
		}

		///
		/// Returns whether recreating ICU indexes is enabled.
		///
		bool getIcu() const
		{
			return icu;
		}

		///
		/// Sets whether recreating ICU indexes is enabled.
		///
		MaintenanceOptions& setIcu(bool value)
		{
			icu = value;
			return *this;
		}

		///
		/// Returns whether database upgrade is enabled.
		///
		bool getUpgradeDb() const
		{
			return upgradeDb;
		}

		///
		/// Sets whether database upgrade is enabled.
		///
		MaintenanceOptions& setUpgradeDb(bool value)
		{
			upgradeDb = value;
			return *this;
		}

	private:
		std::string database;
		ServiceManager::VerboseOutput verboseOutput;
		std::optional<std::uint32_t> parallelWorkers;
		bool sweep = false;
		bool validate = false;
		bool mend = false;
		bool ignoreChecksum = false;
		bool killShadows = false;
		bool full = false;
		bool checkDb = false;
		bool icu = false;
		bool upgradeDb = false;
	};

	///
	/// Executes configuration and maintenance operations through the Firebird service manager.
	///
	class DatabaseManager final : public ServiceManager
	{
	public:
		using ServiceManager::ServiceManager;

	public:
		///
		/// Configures database properties using the provided options.
		///
		void execute(const DatabaseManagerOptions& options);

		///
		/// Runs a maintenance or repair operation using the provided options.
		///
		void execute(const MaintenanceOptions& options);
	};
}  // namespace fbcpp


#endif  // FBCPP_DATABASE_MANAGER_H

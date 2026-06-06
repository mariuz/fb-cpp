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

#include "TestUtil.h"
#include "fb-cpp/MaintenanceManager.h"
#include "fb-cpp/Exception.h"
#include "fb-cpp/Statement.h"
#include "fb-cpp/Transaction.h"
#include <boost/test/unit_test.hpp>

namespace
{
	ServiceManagerOptions makeServiceManagerOptions()
	{
		auto options = ServiceManagerOptions{};

		if (const auto server = getServer())
			options.setServer(server.value());

		return options;
	}
}  // namespace

BOOST_AUTO_TEST_SUITE(MaintenanceManagerSuite)

BOOST_AUTO_TEST_CASE(databaseSweepAndValidate)
{
	const auto databasePath = getTempFile("MaintenanceManager-sweepAndValidate.fdb", false);
	const auto databaseUri = getTempFile("MaintenanceManager-sweepAndValidate.fdb");
	const auto attachmentOptions = AttachmentOptions().setConnectionCharSet("UTF8");

	{  // scope
		Attachment attachment{
			CLIENT, databaseUri, AttachmentOptions().setCreateDatabase(true).setConnectionCharSet("UTF8")};
		Transaction transaction{attachment};

		Statement createTable{attachment, transaction, "create table test (id integer)"};
		BOOST_REQUIRE(createTable.execute(transaction));
		transaction.commit();
	}

	{  // scope
		Attachment attachment{CLIENT, databaseUri, attachmentOptions};
		Transaction transaction{attachment};

		Statement insertData{attachment, transaction, "insert into test (id) values (1)"};
		BOOST_REQUIRE(insertData.execute(transaction));
		transaction.commit();
	}

	MaintenanceManager manager{CLIENT, makeServiceManagerOptions()};

	// 1. Run database sweep
	BOOST_CHECK_NO_THROW(manager.execute(MaintenanceOptions().setDatabase(databasePath).setSweep(true)));

	// 2. Run multi-threaded database sweep
	BOOST_CHECK_NO_THROW(
		manager.execute(MaintenanceOptions().setDatabase(databasePath).setSweep(true).setParallelWorkers(4)));

	// 3. Run database validation
	BOOST_CHECK_NO_THROW(
		manager.execute(MaintenanceOptions().setDatabase(databasePath).setValidate(true).setFull(true)));

	// 4. Run database upgrade (minor ODS upgrade)
	BOOST_CHECK_NO_THROW(manager.execute(MaintenanceOptions().setDatabase(databasePath).setUpgradeDb(true)));

	Attachment cleanup{CLIENT, databaseUri, attachmentOptions};
	cleanup.dropDatabase();
}

BOOST_AUTO_TEST_SUITE_END()

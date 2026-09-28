/****************************************************************************
 * Copyright (c) 2015, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************
 */

#include "utest/utest_harness.h"
#include "utest/utest_stack_trace.h"
#include "utest/unity_handler.h"
#include "greentea-client/test_env.h"
#include "unity/unity.h"

// End only the current test, instead of raise_failure() asserting and stopping the program.
// Only inside RUN_TEST, whose TEST_PROTECT set the jump target.
static bool unity_standalone_test_running()
{
    return !utest::v1::Harness::is_busy() && Unity.CurrentTestName != NULL;
}

void utest_unity_assert_failure(void)
{
    UTEST_LOG_FUNCTION();
    if (unity_standalone_test_running()) {
        Unity.CurrentTestFailed = 1;
        TEST_ABORT(); // JMP
    }
    utest::v1::Harness::raise_failure(utest::v1::REASON_ASSERTION);
}

void utest_unity_ignore_failure(void)
{
    UTEST_LOG_FUNCTION();
    if (unity_standalone_test_running()) {
        Unity.CurrentTestIgnored = 1;
        TEST_ABORT(); // JMP
    }
    utest::v1::Harness::raise_failure(utest::v1::failure_reason_t(utest::v1::REASON_ASSERTION | utest::v1::REASON_IGNORE));
}

void utest_safe_putc(int chr)
{
    greentea_putc(chr);
}

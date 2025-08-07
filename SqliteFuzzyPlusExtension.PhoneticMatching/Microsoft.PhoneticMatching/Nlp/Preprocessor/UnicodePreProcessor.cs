﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

namespace Microsoft.PhoneticMatching.Nlp.Preprocessor
{
    using System;
    using System.Text;

    /// <summary>
    /// Unicode pre-processor
    /// </summary>
    internal class UnicodePreProcessor : IPreProcessor
    {
        /// <summary>
        /// Function to preform the pre-processing with unicode normalization form.
        /// </summary>
        /// <param name="query">The string to pre-process.</param>
        /// <returns>The pre-processed string.</returns>
        public string PreProcess(string query)
        {
            return query == null ? throw new ArgumentNullException("query can't be null") : query.Normalize(NormalizationForm.FormKC);
        }
    }
}

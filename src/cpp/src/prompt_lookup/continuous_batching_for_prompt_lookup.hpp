// Copyright (C) 2023-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "openvino/genai/continuous_batching_pipeline.hpp"

#include "continuous_batching_impl.hpp"

namespace ov::genai {
class ContinuousBatchingPipeline::ContinuousBatchingForPromptLookupImpl : public ContinuousBatchingPipeline::ContinuousBatchingImpl {
public:
    ContinuousBatchingForPromptLookupImpl() = default;

    ContinuousBatchingForPromptLookupImpl(
        const std::shared_ptr<ov::Model>& model,
        const Tokenizer& tokenizer,
        const SchedulerConfig& scheduler_config,
        const std::string& device,
        const ov::AnyMap& properties,
        const ov::genai::GenerationConfig& generation_config,
        bool is_validation_mode_enabled = false) :
    ContinuousBatchingImpl{ model,
                            tokenizer,
                            scheduler_config,
                            device,
                            properties,
                            generation_config,
                            true } {};
                            
    void generate_candidates();

    // { generated_len, validation_len }
    using SequenceLen = std::pair<uint64_t, uint64_t>;
    std::map<uint64_t, SequenceLen> get_generated_request_len();

protected:
    TokenIds generate_candidates(const TokenIds& input_ids, size_t num_pred_tokens, size_t max_ngram_size);
};
}